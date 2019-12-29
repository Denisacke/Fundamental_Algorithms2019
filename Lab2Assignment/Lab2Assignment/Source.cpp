/**
* @author Flueran Robert-Denis
* @group 30423
* Specification of the problem:	We are required to implement correctly and efficiently two methods for building a heap,
								namely the bottom ­up and the top­down strategies. Additionally, we have to implement
								heapsort.

* Personal interpretation: 		HeapSort algorithm works by taking the root of an already built heap and placing it in the right position,
								firstly by swapping it with the last element. Now, there are two methods by which we build the respective heap,
								BottomUp and TopDown, to be more specific. 

								BottomUp works by taking all the parental nodes (starting with the one who finds itself at the lowest level
								out of all the parental nodes) and comparing them with their children and swapping elements, if necessary.
								It performs such actions in the recursive function heapify. It is recursive because, when we find ourselves
								in a higher lever in the tree, we may need to check the parental nodes with their parents until we reach
								the bottom of the tree. It may happen that some nodes must go all the way up in a tree. The heap is built
								by applying heapify to the first half of the array we have to sort, starting from the item position at the half,
								because all the parental nodes find themselves at these positions.

								TopDown works by starting with an empty heap and repeatedly inserting elements and checking if the heap property
								is satisfied. I've tried implementing TopDown using priority queues. Basically, I tried going through the array
								with a for loop from beginning to end and checking the elements one by one with their parents to see if I need
								to swap some of them (that happens in IncreaseKey). The parent of an element positioned at i can be found at the
								position i/2 - 1.

								Complexity-wise, we can observe that BottomUp is the faster way to go, having O(n) time complexity. TopDown has
								O(n * log n) time complexity, but it finds itself to be more efficient when you don't know the number of elements
								that are going to form a heap, as it keeps on adding elements in the heap and checking if the heap property
								is satisfied. BottomUp works better when we have a fixed size for the heap.

								TopDown has O(n * log n) time complexity since IncreaseKey (the function that puts elements in their right position
								in the heap) has O(log n) complexity, and we are calling this function for each element from an array of n elements.
								BottomUp, based on Heapify function, takes about O(1) time in its best case, since it wouldn't have to call itself
								if we have all the elements already sorted. In other cases (when the root has to be sinked to the lowest level
								- that of a leaf), though, it would take O(log n) time.



**/
#include <iostream> 
#include "Profiler.h"
#include <ctime>
using namespace std;
Profiler profiler("Lab2");

int heap_size = 1;
int n, m[5][11000];
int BAssign[5], BCompare[5];
int TAssign[5], TCompare[5];
void GenArrayAvg(int n) {
	int i, j;
	for (i = 0; i < 5; i++)
		for (j = 0; j < n; j++)
			m[i][j] = rand() % n + 1;
}

void heapify(int v[], int n, int i, int index) {

	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	///BCompare[index] += 2;
	profiler.countOperation("BottomUpOp", n, 2);
	if (l < n && v[l] > v[largest])
		largest = l;


	if (r < n && v[r] > v[largest])
		largest = r;
	if (largest != i) {

		swap(v[i], v[largest]);
		profiler.countOperation("BottomUpOp", n, 3);
		///BAssign[index] += 3;

		heapify(v, n, largest, index);
	}
}

void BuildHeapBU(int v[], int index, int n) {
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(v, n, i, index);
}

void HeapSortBU(int v[], int index, int n) {

	BuildHeapBU(v, index, n);


	for (int i = n - 1; i >= 0; i--) {

		swap(v[0], v[i]);


		heapify(v, i, 0, index);
	}
}



void printArray(int v[], int n) {
	for (int i = 0; i < n; ++i)
		cout << v[i] << " ";
	cout << "\n";
}


void IncreaseKey(int v[], int i, int key, int index) {

	///v[i] = key;
	profiler.countOperation("TopDownOp", n);
	if (v[0] < v[i]) {
		profiler.countOperation("TopDownOp", n, 3);
		swap(v[0], v[i]);
	}
		
	int j = i;
	int k = 0;
	while (i > 1 && v[i / 2 - 1] < v[i]) {
		swap(v[i / 2 - 1], v[i]);
		profiler.countOperation("TopDownOp", n, 3);
		///TAssign[index] += 3;
		i = i / 2 - 1;
		k++;
	}
	if (j == i) {
		profiler.countOperation("TopDownOp", n);
		///TCompare[index]++;
	}
	else {
		profiler.countOperation("TopDownOp", n, k);
		///TCompare[index] += k;
	}
		
}

void MaxInsertion(int v[], int key, int index, int n) {

	heap_size++;
	///v[heap_size] = 999999;
	///TAssign[index]++;
	IncreaseKey(v, heap_size, key, index);
}

void BuildHeapTD(int v[], int index, int n) {

	heap_size = 0;
	for (int i = 1; i < n; i++) {
		heap_size++;
		IncreaseKey(v, heap_size, v[i], index);
	}
		
}

void HeapSortTD(int v[], int index, int n) {
	BuildHeapTD(v, index, n);

	for (int i = n - 1; i >= 0; i--) {
		swap(v[0], v[i]);
		heapify(v, i, 0, index);
	}
}

int sumB, sumT;
int main() {


	int arr[] = { 32, 47, 13, 5, 6, 7, 21 };
	int arr2[] = { 21, 47, 13, 5, 6, 7, 32 };

	HeapSortBU(arr, 5, 7);
	printArray(arr, 7);
	HeapSortTD(arr2, 5, 7);
	printArray(arr2, 7);
	Sleep(2000);
	n = 100;
	for (n = 100; n <= 10000; n += 100) {

		srand(time(NULL));
		GenArrayAvg(n);
		int v[10000];
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < n; j++)
				v[j] = m[i][j];
			BuildHeapBU(v, i, n);
			BuildHeapTD(m[i], i, n);
		}
		for (int i = 0; i < 5; i++) {
			sumB += BAssign[i] + BCompare[i];
			sumT += TAssign[i] + TCompare[i];
		}
		///profiler.countOperation("BottomUpOperations", n, sumB / 5);
		///profiler.countOperation("TopDownOperations", n, sumT / 5);
	}
	profiler.divideValues("BottomUpOp", 5);
	profiler.divideValues("TopDownOp", 5);
	profiler.createGroup("Operations", "BottomUpOp", "TopDownOp");
	profiler.showReport();
	return 0;
}
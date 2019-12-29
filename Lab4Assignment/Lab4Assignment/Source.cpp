/**
* @author Flueran Robert-Denis
* @group 30423
* Specification of the problem:	We are required to implement correctly and efficienty method for merging k sorted sequences, where n is the
								total number of elements.

* Personal interpretation: 		I have managed to perfom the merging algorithm in O(n * logk) time. I have used a vector of vectors in which I
								store all the sorted lists, declared a "heap" array in which I firstly put the first element from each list and
								built a min-heap. When I found that the root of the heap came from a vector that can't provide another element
								for the root (it is basically empty, so we can't take elements from it), instead of decreasing the size of
								the heap, I have equaled the root of the heap (its value) to INT_MAX, because building the min-heap would 
								result in putting the index of the empty vector at the bottom of the heap, such that it wouldn't bother us 
								anymore.
								
								At first, I looped through a for loop where n varied from 100 to 10000 and performed the algorithm for three cases
								(k = 5, k = 10 and k = 100). We can observe from the graphs that, although the number of elements is the same,
								splitting them into more and more sorted sequences, we are performing many more operations. That's why k also
								plays a part in calculating the running time for the algorithm.
								
								Afterwards, I set n to 10000 elements and varied k from 10 to 500. As expected, the running time grew as we
								incremented k.

								I have written a method that checks at every step if the finalArray is sorted, but I am still gonna make a small
								demo input, since it is required..
**/

#include <iostream>
#include <list>
#include <vector>
#include <ctime>
#include <limits>
#include <algorithm>
#include "Profiler.h"
using namespace std;
Profiler profiler("Lab4");
int n;
struct elem {

	int val;
	int index;
};
vector <elem> ::iterator it;
vector <int> ::iterator itr;
vector<vector<elem>> v;
elem heap[10000];
int k = 5;
elem aux[10000];
int opCount[4];
int val[10000];
vector<int> finalArray;

void genRandomArray(elem v[], int size) {
	for (int i = 0; i < size; i++)
		v[i].val = rand() % 101 + 1;
}
void heapify(elem v[], int size, int i, int index) {

	int smallest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	opCount[index] += 2;
	if (l < size && v[l].val < v[smallest].val)
		smallest = l;


	if (r < size && v[r].val < v[smallest].val)
		smallest = r;
	if (smallest != i) {

		elem aux = v[i];
		v[i] = v[smallest];
		v[smallest] = aux;
		opCount[index] += 3;

		heapify(v, size, smallest, index);
	}
}

void BuildHeapBU(elem v[], int n, int index) {
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(v, n, i, index);
}

void heapSort(elem v[], int n, int index) {

	BuildHeapBU(v, n, index);


	for (int i = n - 1; i >= 0; i--) {

		elem aux = v[0];
		v[0] = v[i];
		v[i] = aux;

		heapify(v, i, 0, index);
	}
}

void printArray(elem arr[], int size) {
	int i;
	for (i = 0; i < size; i++)
		cout << arr[i].val << " ";
	cout << endl;
}


void checkIfSorted() {
	for(int i = 0; i < finalArray.size() - 1; i++)
		if (finalArray[i] > finalArray[i + 1]) {
			cout << "Array not sorted" << '\n';
			return;
		}
	cout << "Array is sorted\n";
}

void setFinalArray(int index) {
	while (finalArray.size() < n) {
		BuildHeapBU(heap, k, index);
		it = v[heap[0].index].begin();
		if(v[heap[0].index].size() != 0)
			v[heap[0].index].erase(it);

		finalArray.push_back(heap[0].val);
		opCount[index] += 3;
		if (v[heap[0].index].size() < 1)
			heap[0].val = INT_MAX;
		else
			heap[0] = v[heap[0].index].front();
	}
	checkIfSorted();
}

void buildLists(int index) {
	for (n = 100; n <= 10000; n += 100) {
		finalArray.clear();
		v.clear();
		v.resize(k);
		for (int j = 0; j < 4; j++)
			opCount[j] = 0;
		for (int j = 0; j < k; j++) {
			v[j].clear();
			FillRandomArray(val, n / k, 1, n, false, 1);
			for (int i = 0; i < n / k; i++) {
				aux[i].index = j;
				aux[i].val = val[i];
			}
			for (int i = 0; i < n / k; i++) {
				v[j].push_back(aux[i]);
			}
			v[j].resize(n / k);
		}
		for (int i = 0; i < k; i++)
			heap[i] = v[i].front();
		setFinalArray(index);
		if (index == 0)
			profiler.countOperation("kEquals5", n, opCount[index] + k);
		else
			if (index == 1)
				profiler.countOperation("kEquals10", n, opCount[index] + k);
			else
				if(index == 2)
					profiler.countOperation("kEquals100", n, opCount[index] + k);
	}
}

elem demoHeap[1000];
vector<vector<elem>> demo;
void demoTest() {
	finalArray.clear();
	demo.clear();
	demo.resize(k);
	for (int i = 0; i < k; i++) {
		demo[i].clear();
		FillRandomArray(val, n / k, 1, n, false, 1);
		for (int j = 0; j < n / k; j++) {
			aux[j].index = j;
			aux[j].val = val[j];
			demo[i].push_back(aux[j]);
		}
			
		demo[i].resize(n / k);
	}
	for (int i = 0; i < k; i++)
		demoHeap[i] = demo[i].front();
	while (finalArray.size() < n) {
		BuildHeapBU(demoHeap, k, 4);
		it = demo[demoHeap[0].index].begin();
		if (demo[demoHeap[0].index].size() != 0)
			demo[demoHeap[0].index].erase(it);
		finalArray.push_back(demoHeap[0].val);
		///if (demo[demoHeap[0].index].size() < 1)
		///	demoHeap[0].val = INT_MAX;
		///else
		///	demoHeap[0] = demo[demoHeap[0].index].front();
	}
	for (int i = 0; i < finalArray.size(); i++)
		cout << finalArray[i] << " ";
	cout << '\n';
		

}
int main() {
	
	
	k = 4;
	n = 20;
	vector<vector<elem>> demo;
	cout << "This is the demo test case! The program will sleep for 10 seconds such that you can see it\n";
	cout << "The initial size of the array is: " << finalArray.size() << '\n';
	demoTest();
	cout << "The final size is: " << finalArray.size() << '\n';
	Sleep(10000);
	
	k = 5;
	buildLists(0);

	k = 10;
	buildLists(1);

	k = 100;
	buildLists(2);
	
	n = 10000;
	for (k = 10; k <= 500; k += 10) {
		finalArray.clear();
		v.clear();
		v.resize(k);
		for (int j = 0; j < 4; j++)
			opCount[j] = 0;
		for (int j = 0; j < k; j++) {
			v[j].clear();
			FillRandomArray(val, n / k, 1, n, false, 1);
			for (int i = 0; i < n / k; i++) {
				aux[i].index = j;
				aux[i].val = val[i];
			}
			for (int i = 0; i < n / k; i++) {
				v[j].push_back(aux[i]);
			}
			v[j].resize(n / k);
		}
		for (int i = 0; i < k; i++)
			heap[i] = v[i].front();
		setFinalArray(3);
		profiler.countOperation("nConstant_kVaries_Op", k, opCount[3] + k);
	}
	profiler.createGroup("kConstant_nVaries_Op", "kEquals5", "kEquals10", "kEquals100");
	profiler.showReport();
	return 0;
}
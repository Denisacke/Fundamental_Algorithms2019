/**
* @author Flueran Robert-Denis
* @group 30423
* Specification of the problem:	We are required to implement QuickSort and QuickSelect and perform a comparative analysis of QuickSort and 
								HeapSort.

* Personal interpretation: 		I have implemented QuickSort by using the last element as pivot. The matrix of rows is used for the average case,
								where I have to compute the average of the number of ops it takes to sort five average arrays (represented by the
								five rows of the matrix). I've prepared a small demo given in the form of an array with harcoded values
								to demonstrate that QuickSort and QuickSelect are correct.

								I have implemented HeapSort by using the BottomUp method of building the heap, since it is the fastest way to go.
								Even so, HeapSort appears to be less efficient than QuickSort in the average case. It has a better worst case
								run time, though ( O(n * log n), compared to O(n ^ 2) for QuickSort). This means that it is an optimal algorithm.
								QuickSort isn't optimal, since its worst case takes more time than n * log n.

								To achieve the worst case for QuickSort, I have called the same method with last elements as pivot, but used a
								sorted array, which would result in the sorting algorithm doing a lot of operations. For its best case, I called
								quickSort for an ascendingly sorted array and chose the middle of the array as a pivot, such that it would split
								the array into two equal parts. We can see that the average-case of QuickSort is pretty close to its best case.



**/
#include "Profiler.h"
#include <iostream>
#include <ctime>
#include <limits>
using namespace std;
Profiler profiler("Lab3");
int n, m[5][10000];
int best[10000], worst[10000];
int BestOp, WorstOp;
void GenArrayAvg(int n) {
	int i, j;
	for (i = 0; i < 5; i++)
		for (j = 0; j < n; j++)
			m[i][j] = rand() % n + 1;
}

void printArray(int arr[], int size) {
	int i;
	for (i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl;
}

int partition(int arr[], int low, int high, int index){

	int pivot;
	if (index == 1)
		pivot = arr[(high + low) / 2];
	else
		pivot = arr[high];
	int i = (low - 1); 
	if (index == 0)
		profiler.countOperation("QuickSortOp", n, 1);
	else
		if (index == 1)
			profiler.countOperation("QuickBest", n);
		else
			profiler.countOperation("QuickWorst", n);
	for (int j = low; j <= high - 1; j++){
		if (index == 0)
			profiler.countOperation("QuickSortOp", n, 1);
		else
			if (index == 1)
				profiler.countOperation("QuickBest", n);
			else
				profiler.countOperation("QuickWorst", n);

		if (arr[j] < pivot){
			i++; 
			if (index == 0)
				profiler.countOperation("QuickSortOp", n, 3);
			else
				if (index == 1)
					profiler.countOperation("QuickBest", n, 3);
				else
					profiler.countOperation("QuickWorst", n, 3);

			swap(arr[i], arr[j]);
		}
	}
	if (index == 0)
		profiler.countOperation("QuickSortOp", n, 3);
	else
		if (index == 1)
			profiler.countOperation("QuickBest", n, 3);
		else
			profiler.countOperation("QuickWorst", n, 3);

	swap(arr[i + 1], arr[high]);
	return i + 1;
}

void quickSort(int arr[], int low, int high, int index){

	if (low < high){
		int pi = partition(arr, low, high, index);
		quickSort(arr, low, pi - 1, index);
		quickSort(arr, pi + 1, high, index);
	}
}

void heapify(int v[], int size, int i) {

	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	profiler.countOperation("HeapOp", n, 2);
	if (l < size && v[l] > v[largest])
		largest = l;


	if (r < size && v[r] > v[largest])
		largest = r;
	if (largest != i) {

		swap(v[i], v[largest]);
		profiler.countOperation("HeapOp", n, 3);

		heapify(v, size, largest);
	}
}

void BuildHeapBU(int v[], int n) {
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(v, n, i);
}

void heapSort(int v[], int n) {

	BuildHeapBU(v, n);


	for (int i = n - 1; i >= 0; i--) {

		swap(v[0], v[i]);
		profiler.countOperation("HeapOp", n, 3);

		heapify(v, i, 0);
	}
}


int QuickSelect(int arr[], int left, int right, int k){

	if (k > 0 && k <= right - left + 1) {

		int index = partition(arr, left, right, 0);

		if (index - left == k - 1)
			return arr[index];

		if (index - left > k - 1)
			return QuickSelect(arr, left, index - 1, k);

		return QuickSelect(arr, index + 1, right, k - index + left - 1);
	}
	return INT_MAX;
}



int main(){

	int arr[] = { 10, 7, 8, 9, 1, 5, 2, 1, 9 };
	n = sizeof(arr) / sizeof(arr[0]);
	cout << "Current array: \n";
	printArray(arr, n);
	quickSort(arr, 0, n - 1, 0);
	cout << "Sorted array: \n";
	printArray(arr, n);
	cout << "The 5th smallest element is: " << QuickSelect(arr, 0, n - 1, 5) << '\n';
	profiler.reset("QuickSortOp");
	n = 100;
	for (n = 100; n <= 10000; n += 100) {

		srand(time(NULL));
		GenArrayAvg(n);
		int v[10000];
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < n; j++)
				v[j] = m[i][j];
			heapSort(m[i], n);
			quickSort(v, 0, n - 1, 0);
		}
		FillRandomArray(best, n, 1, n, false, 1);
		FillRandomArray(worst, n, 1, n, false, 2);
		quickSort(best, 0, n - 1, 1);
		quickSort(worst, 0, n - 1, 2);

	}
	profiler.divideValues("QuickSortOp", 5);
	profiler.divideValues("HeapOp", 5);
	profiler.createGroup("Sort_Comparison", "QuickSortOp", "HeapOp");
	profiler.showReport();
	return 0;
}
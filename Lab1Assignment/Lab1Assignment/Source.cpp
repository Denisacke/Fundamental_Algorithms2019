/**
* @author Flueran Robert-Denis
* @group 30423
* Specification of the problems:	Compare 3 direct sorting methods (best, average and worst case), i.e.
									implementation, exemplify correctness and analysis (charts) and interpret the charts

* Personal interpretation: 			I had to compare SelectionSort, InsertionSort and BubbleSort (no. of assignments, comparisons, total)
									at their best, worst, and average case. In order to compute the number of operations
									I have taken a matrix of 6 rows of 100000 elements max (because I had to count the no of operations for 
									five random arrays and compute their average) and two arrays of 10000 elements max, one that would be sorted
									in ascending order, and the other one in descending order.

									Because the process of computing all the things and sorting arrays of hundreds or thousands of elements
									took a lot for my computer to process and plot graphs out of, I've decided to take some long long arrays of
									8 elements, in which I store the number of operations (BAssign = no of assign operations in BubbleSort)
									for each array or matrix row. I wanted to reduce the calling of countOperation to a minimum, so I made
									the program such that I would only call it once and increment it with one of an element of 
									one of the long long arrays.
									The indexes from 0 to 4 are for the average "arrays" stored in the matrix rows,
									index 5 is for the best case and index 6 is for the worst one..I haven't declared arrays for total
									no. of operations, since I could just add one Assign array with its respective Compare array.

									All the sorting algorithms are stable. I have added an extra condition to SelectionSort at the end to make
									it stable (if (v[position] != v[i]). No algorithm out of the three can swap terms that are equal. In order
									to test if the algorithms are correct, I have prepared a small input size, given in the form of an array
									declared in the main function (int v[]). I have left the index 7 from the long long arrays for this test
									case.

									What can be seen from the plotted graphs is that BubbleSort is the worst algorithm to go for in the average
									and worst cases. In the best cases, though, it performs really well, since the stable version of BubbleSort 
									does virtually NO assignments and only comparisons. The stable version of SelectionSort also does ZERO
									assign operations in its best case (since it doesn't even swap the terms that are equal), but it performs
									many comparisons, making it the worst algorithm to go for in the best case (TotalBest, CompareBest).

									BubbleSort manages to do so many operations that the size of the variable incremented in profiler.countOperation
									(which probably is an int, because it resets its value at about 4 billion) can't handle the 
									huge number of operations. Because of this, we see the values falling from 4 billion to a few tens of 
									thousands at some points in the graphs when we are trying to compute the TotalAverage, TotalWorst, 
									CompareWorst and AssignWorst (where BubbleSort performs muuuch worse when compared to the other sorting 
									algorithms). Even though the long long type of the arrays would make them handle the large numbers, I would have
									had to change stuff in the Profiler header in order for it to plot graphs with such numbers

									Since we've established which algorithm is the worst, let's compare the other two. As it can be seen 
									from the graphs, InsertionSort is more efficient that SelectionSort in the best case (TotalBest). 
									When we look at the worst case, things are a little different, SelectionSort being much more efficient.
									In the average case, there isn't such a big difference between the two algorithms.

									The application takes about 3 minutes in Release mode to plot all the graphs.
									
**/

#include "Profiler.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <string.h>
#define MAX_SIZE 2000
using namespace std;
Profiler profiler("Lab1");
int m[5][10000];
int n, best[10000], worst[10000];
long long BAssign[7], BCompare[7];
long long IAssign[7], ICompare[7];
long long SAssign[7], SCompare[7];

void GenArrayAvg(int n) {
	int i, j;
	for (i = 0; i < 5; i++)
		for (j = 0; j < n; j++)
			m[i][j] = rand() % n + 1;
}


void SelectionSort(int Array[], int n, int index) {
	int i, j, position;
	int v[10000];
	for (i = 0; i < n; i++)
		v[i] = Array[i];
	for (i = 0; i < n - 1; i++) {
		position = i;
		for (j = i + 1; j < n; j++) {
			SCompare[index]++;
			if (v[j] < v[position])
				position = j;
		}
			
		SCompare[index]++;
		if (v[position] != v[i]) {
			swap(v[i], v[position]);
			SAssign[index] += 3;
		}
			
	}
	if (index == 7) {
		for (i = 0; i < n; i++)
			cout << v[i] << " ";
		cout << '\n';
	}

}

void BubbleSort(int Array[], int n, int index) {

	int i;
	bool isSwapped = 1;
	int v[10000];
	for (i = 0; i < n; i++)
		v[i] = Array[i];
	while (isSwapped) {
		isSwapped = 0;
		for (i = 0; i < n - 1; i++) {
			BCompare[index]++;
			if (v[i] > v[i + 1]) {
				isSwapped = 1;
				BAssign[index] += 3;
				swap(v[i], v[i + 1]);
			}
		}		
	}
	if (index == 7) {
		for (i = 0; i < n; i++)
			cout << v[i] << " ";
		cout << '\n';
	}
}

void InsertionSort(int Array[], int n, int index) {

	int i, j;
	int v[10000];
	for (i = 0; i < n; i++)
		v[i] = Array[i];
	for (i = 1; i < n; i++) {
		j = i - 1;
		int aux = v[i];
		IAssign[index]++;
		int k = j;
		while (j >= 0 && aux < v[j]) {
			v[j + 1] = v[j];
			IAssign[index]++;
			j--;
		}
		if (k == j)
			ICompare[index]++;
		else
			ICompare[index] += k - j;
		ICompare[index]++;
		if (v[j + 1] > aux) {
			IAssign[index]++;
			v[j + 1] = aux;
		}
			
	}
	if (index == 7) {
		for (i = 0; i < n; i++)
			cout << v[i] << " ";
		cout << '\n';
	}
}

void SelectionAvg(int n, int index) {
	int i, j, position;
	int v[10000];
	for (i = 0; i < n; i++)
		v[i] = m[index][i];
	for (i = 0; i < n - 1; i++) {
		position = i;
		for (j = i + 1; j < n; j++) {
			SCompare[index]++;
			if (v[j] < v[position])
				position = j;
		}
		SCompare[index]++;
		if (v[position] != v[i]) {
			swap(v[i], v[position]);
			SAssign[index] += 3;
		}
		

	}
}

void BubbleAvg(int n, int index) {
	int i;
	bool isSwapped = 1;
	int v[10000];
	for (i = 0; i < n; i++)
		v[i] = m[index][i];
	while (isSwapped) {
		isSwapped = 0;
		for (i = 0; i < n - 1; i++) {
			BCompare[index]++;
			if (v[i] > v[i + 1]) {
				isSwapped = 1;
				BAssign[index] += 3;
				swap(v[i], v[i + 1]);
			}
		}


	}
}

void InsertionAvg(int n, int index) {
	int i, j;
	int v[10000];
	for (i = 0; i < n; i++)
		v[i] = m[index][i];
	for (i = 1; i < n; i++) {
		j = i - 1;
		int aux = v[i];
		IAssign[index]++;
		int k = j;
		while (j >= 0 && aux < v[j]) {
			v[j + 1] = v[j];
			IAssign[index]++;
			j--;
		}
		ICompare[index] += k - j + 1;
		if (v[j + 1] > aux) {
			IAssign[index]++;
			v[j + 1] = aux;
		}

	}
}
long long sumA, sumB;
int main() {

	n = 100;
	int v[] = { 2, 7, 4, 5, 1, 8 };
	SelectionSort(v, 6, 7);
	InsertionSort(v, 6, 7);
	BubbleSort(v, 6, 7);
	for (n = 100; n <= 10000; n += 100) {
		srand(time(NULL));
		GenArrayAvg(n);
		for (int j = 0; j < 5; j++) {
			SelectionAvg(n, j);
			BubbleAvg(n, j);
			InsertionAvg(n, j);
		}
		for (int j = 0; j < 5; j++) {
			sumA += SAssign[j];
			sumB += SCompare[j];
		}
		profiler.countOperation("SelectAssignAvg", n, sumA / 5);
		profiler.countOperation("SelectCompareAvg", n, sumB / 5);
		profiler.countOperation("SelectTotalAvg", n, (sumA + sumB) / 5);

		sumA = sumB = 0; //Ik it's not that great to recycle the same variables for multiple operations, but I didn't wanna declare any more variables
		for (int j = 0; j < 5; j++) {
			sumA += BAssign[j];
			sumB += BCompare[j];
		}
		profiler.countOperation("BubbleAssignAvg", n, sumA / 5);
		profiler.countOperation("BubbleCompareAvg", n, sumB / 5);
		profiler.countOperation("BubbleTotalAvg", n, (sumA + sumB) / 5);

		sumA = sumB = 0;
		for (int j = 0; j < 5; j++) {
			sumA += IAssign[j];
			sumB += ICompare[j];
		}
		profiler.countOperation("InsertAssignAvg", n, sumA / 5);
		profiler.countOperation("InsertCompareAvg", n, sumB / 5);
		profiler.countOperation("InsertTotalAvg", n, (sumA + sumB) / 5);

		FillRandomArray(best, n, 1, n, false, 1);
		SelectionSort(best, n, 5);
		BubbleSort(best, n, 5);
		InsertionSort(best, n, 5);
		profiler.countOperation("SelectAssignBest", n, SAssign[5]);
		profiler.countOperation("BubbleAssignBest", n, BAssign[5]);
		profiler.countOperation("InsertAssignBest", n, IAssign[5]);
		profiler.countOperation("SelectCompareBest", n, SCompare[5]);
		profiler.countOperation("BubbleCompareBest", n, BCompare[5]);
		profiler.countOperation("InsertCompareBest", n, ICompare[5]);
		profiler.countOperation("SelectTotalBest", n, SAssign[5] + SCompare[5]);
		profiler.countOperation("BubbleTotalBest", n, BAssign[5] + BCompare[5]);
		profiler.countOperation("InsertTotalBest", n, IAssign[5] + ICompare[5]);

		FillRandomArray(worst, n, 1, n, false, 2);
		SelectionSort(worst, n, 6);
		BubbleSort(worst, n, 6);
		InsertionSort(worst, n, 6);
		profiler.countOperation("SelectAssignWorst", n, SAssign[6]);
		profiler.countOperation("BubbleAssignWorst", n, BAssign[6]);
		profiler.countOperation("InsertAssignWorst", n, IAssign[6]);
		profiler.countOperation("SelectCompareWorst", n, SCompare[6]);
		profiler.countOperation("BubbleCompareWorst", n, BCompare[6]);
		profiler.countOperation("InsertCompareWorst", n, ICompare[6]);
		profiler.countOperation("SelectTotalWorst", n, SAssign[6] + SCompare[6]);
		profiler.countOperation("BubbleTotalWorst", n, BAssign[6] + BCompare[6]);
		profiler.countOperation("InsertTotalWorst", n, IAssign[6] + ICompare[6]);
	}
	profiler.createGroup("TotalBest", "BubbleTotalBest", "SelectTotalBest", "InsertTotalBest");
	profiler.createGroup("TotalWorst", "BubbleTotalWorst", "SelectTotalWorst", "InsertTotalWorst");
	profiler.createGroup("CompareWorst", "BubbleCompareWorst", "SelectCompareWorst", "InsertCompareWorst");
	profiler.createGroup("CompareBest", "BubbleCompareBest", "SelectCompareBest", "InsertCompareBest");
	profiler.createGroup("AssignBest", "BubbleAssignBest", "SelectAssignBest", "InsertAssignBest");
	profiler.createGroup("AssignWorst", "BubbleAssignWorst", "SelectAssignWorst", "InsertAssignWorst");
	profiler.createGroup("AssignAvg", "BubbleAssignAvg", "SelectAssignAvg", "InsertAssignAvg");
	profiler.createGroup("CompareAvg", "BubbleCompareAvg", "SelectCompareAvg", "InsertCompareAvg");
	profiler.createGroup("TotalAvg", "BubbleTotalAvg", "SelectTotalAvg", "InsertTotalAvg");
	profiler.showReport();
	return 0;
}
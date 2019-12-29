/**
* @author Flueran Robert-Denis
* @group 30423
* Specification of the problem:	We are required to evaluate the search operation for hash tables using open addressing and
								quadratic probing, in the average case

* Personal interpretation: 		I set the size of the hash table to 9973, since it is a prime number close to 10000. I've set an array of double
								elements that contains all the fill factors and used it to compute the number of elements to insert at each step.
								
								In order to perform the uniform selection for the found elements, I've generated an array of 1500 random and 
								unique elements and inserted its elements in the hash table. I've made sure that other elements that have to be 
								inserted (from 1500 to n) are different from the 1500 unique random elements. This way, it's certain that the
								1500 random elements that are going to be found in the hash table have the same probability to be found (since
								each one of them appears only once in the hash table). The "not found" elements have been provided from an array
								that's filled with random numbers with values between 10000 and 15000.

								The number of cells accessed is stored in four variables (sumFound, sumNotFound, maxFound, MaxNotFound) which
								have their values set to 0 before each computation. I have performed the operations for each fillFactor five
								times, so I have to divide sumFound and sumNotFound by 1500 (coming from the number of elements searched) * 5
								(coming from the number of times I perform the operations for a single fillFactor).

								The number of cells accessed in the situation where the elements are found is much smaller when compared to
								the number of cells the algorithm has to access in order to figure out that an element isn't in the hash table.
								Still, that doesn't mean that "found" elements are found immediately, as you can see from the Max Effort found
								column. Increasing the fillFactor leads to an increase in the number of cells accessed as well, especially for the 
								"not found" elements.


**/

#include <iostream>
#include <cstring>
#include "Profiler.h"
using namespace std;

Profiler profiler("Lab5");
struct Entry {
	int id;
	char name[30];
};

Entry hashTable[9973];
int freq[9973];
int freq2[9973];
int found[5][2000], notFound[5][2000];
double fillFactor[] = { 0.8, 0.85, 0.9, 0.95, 0.99 };
Entry random[9973];
int n;
int maxFound, sumFound, maxNotFound, sumNotFound;
int hashFunction(int nr, int i) {

	return (nr + 101 * i + 31 * i * i) % 9973;
}

void genRandomArray() {
	srand(time(NULL));
	int i = 0;
	while (i < 1500) {
		random[i].id = rand() % 9973;
		while (freq[random[i].id])
			random[i].id = rand() % 9973;
		freq[random[i].id] = 1;
		strcpy_s(random[i].name, "Test");
		i++;
	}
}

void insert(int key) {
	int i, pos;
	for (i = 0; i < 9973; i++){
		pos = hashFunction(key, i);
		if (hashTable[pos].id == -1){
			hashTable[pos].id = key;
			return;
		}
	}
}

void initTable() {
	for (int i = 0; i < 9973; i++) {
		hashTable[i].id = -1;
		strcpy_s(hashTable[i].name, "Test");
	}

}


int search(int key) {

	int i, pos;
	for (i = 0; i < 9973; i++)
	{
		pos = hashFunction(key, i);
		if (hashTable[pos].id == -1) {
			sumNotFound += i + 1;
			if (maxNotFound < i + 1)
				maxNotFound = i + 1;
			return 0;
		}
		else
			if (hashTable[pos].id == key) {
				sumFound += i + 1;
				if (maxFound < i + 1)
					maxFound = i + 1;
				return 1;
			}
	}
	return 0;
}


int main() {
	initTable();
	Entry sample;
	sample.id = 5;
	strcpy_s(sample.name, "Lab");
	insert(sample.id);

	Entry test;
	test.id = 17;
	strcpy_s(test.name, "Test");
	if (search(sample.id) == 1)
		cout << sample.name << " has been found in the hashTable!\n";
	else
		cout << sample.name << " has not been found :(\n";
	if (search(test.id) == 1)
		cout << test.name << " has been found in the hashTable!\n";
	else
		cout << test.name << " has not been found :(\n";
	Sleep(2000);

	cout << "Filling factor\t" << "Avg. Effort found\t" << "Max. Effort found\t" << "Avg. Effort not-found\t" << "Max. Effort not-found\n";
	cout << "-------------------------------------------------------------------------------------------------------------\n";
	for (int k = 0; k < 5; k++) {

		maxFound = maxNotFound = sumFound = sumNotFound = 0;
		for (int i = 0; i < 5; i++) {

			n = (int)(fillFactor[k] * 9973);
			initTable();
			for (int j = 0; j < 9973; j++)
				freq[j] = 0;
			genRandomArray();
			srand(time(NULL));
			int v[1500];
			FillRandomArray(v, 1500, 10000, 15000, true, 0);
			
			for (int j = 1500; j < n; j++) {
				Entry sample;
				sample.id = rand() % 9973;
				strcpy_s(sample.name, "Test");
				while (freq[sample.id])
					sample.id = rand() % 9973;
				insert(sample.id);
			}
			for (int j = 0; j < 1500; j++)
				insert(random[j].id);
			for (int j = 0; j < 1500; j++)
				search(random[j].id);
			for (int j = 0; j < 1500; j++)
				search(v[j]);
			

		}
		cout << fillFactor[k] << "\t\t\t" << (float)sumFound / (1500 * 5) << "\t\t\t" << maxFound << "\t\t\t" << (float)sumNotFound / (1500 * 5) << "\t\t\t" << maxNotFound << "\n";
	}
	Sleep(100000);

	return 0;
}
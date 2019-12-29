/**
* @author Flueran Robert-Denis
* @group 30423
* Specification of the problem:	We are required to implement correctly and efficiently the management operations of an order
								statistics tree. We have to use a balanced, augmented Binary Search Tree. Each node in the tree holds, besides
								the necessary information, also the size field (i.e. the size of the sub-tree rooted at the node).


* Personal interpretation: 		For the Binary Tree, I have made a node class, that has data, size and left and right child as fields. The 
								newNode method is meant to initialize a new node with default values.

								The BuildTree method build a balanced BST tree using a divide and conquer approach (it splits the initial array
								in halves and inserts the middle each time).

								I took OS_Select from Cormen's book and changed it such that the algorithm doesn't access null locations of data.
								It's job is to select the i-th smallest element from a tree.

								OS_Delete is similar to the algorithm for deleting a node in a regular BST. The only difference consists in 
								updating the "size" field of each node after a deletion. I've done this by decreasing the size of a node at each
								call of OS_Delete. OS_Delete solves all cases possible : when the node that has to be deleted is a leaf, when it has
								one child or two children.
								
								Both OS_Select and OS_Delete are PROPORTIONAL to the height of the tree, so their complexity would be O(log n).
								BuildTree takes O(n) time, since we are building it from an array of n elements and we have to insert each element.
								Inserting an element takes O(1) time, but we have n such elements. Of course, making sure that we assign the right
								size to each node would mean making more than just n operations, but the complexity ( O(n) ) stays the same.

								I have generated two graphs : the first one is used to compare the three management operations : BuildTree, 
								OS_Select and OS_Delete; the second graph represents the total number of operations of the application.

								We can observe from the graphs that all the management operations are linear. Delete takes the cake when it comes
								to the largest number of operations. It is followed by Select, which is pretty close to Delete, since both take
								O(n * log n) time (since we are calling the operations n times). BuildTree takes several times less operations than
								the other two. We only call BuildTree once at every n (that varies from 100 to 10000), so it takes O(n) time.
**/


#include <iostream>
#include <random>
#include "Profiler.h"
#include <string>
using namespace std;
Profiler profiler("Lab6");
class node{
public:
	int data;
	node* left;
	node* right;
	int size;
};

node* newNode(int data) {
	node* nod = new node();
	nod->data = data;
	nod->left = NULL;
	nod->right = NULL;
	nod->size = 1;
	return nod;
}

///node* newNode(int data);
node* nodeDelete;
int n;
long long assignB, compareB;
long long assignS, compareS;
long long assignD, compareD;
node* BuildTree(int arr[], int start, int end){
	
	if (start > end)
		return NULL;
	
	
	int mid = (start + end) / 2;
	node *root = newNode(arr[mid]);
	assignB++;
	root->left = BuildTree(arr, start, mid - 1);
	assignB++;
	compareB += 2;
	if (root->left) {
		assignB++;
		root->size += root->left->size;
	}
		
	root->right = BuildTree(arr, mid + 1, end);
	assignB++;
	
	if (root->right) {
		assignB++;
		root->size += root->right->size;
	}
		
	return root;
}

node* OS_Select(node* nod, int i) {
	compareS++;
	if (nod != NULL){
		int r;
		if (nod->left != NULL) {
			assignS++;
			r = nod->left->size + 1;
		}
		else
			r = 1;
		if (i == r)
			return nod;
		else{
			if (i < r) 
				return OS_Select(nod->left, i);
			else 
				return OS_Select(nod->right, i - r);
		}
	}
	else 
		return NULL;
	
}
node* findMin(node* nod){
	node* current = nod;

	while (current && current->left != NULL) {
		assignD++;
		current = current->left;
	}
		
	return current;
}

node* OS_Delete(node* root, int key){
	
	if (root == NULL) 
		return root;

	root->size--;
	
	if (key < root->data) {
		assignD++;
		compareD++;
		root->left = OS_Delete(root->left, key);
	}	
	else 
		if (key > root->data) {
			assignD++;
			compareD++;
			root->right = OS_Delete(root->right, key);
		}
	else{
		compareD += 2;
		if (root->left == NULL){
			node *temp = root->right;
			assignD++;
			delete root;
			///temp->size = root->size;
			return temp;
		}
		else
			if (root->right == NULL){
			node *temp = root->left;
			assignD++;
			delete root;
			///temp->size = root->size;
			return temp;
			}

		node* temp = findMin(root->right);
		assignD++;
		root->data = temp->data;
		root->right = OS_Delete(root->right, temp->data);
		assignD += 2;
	}
	return root;
}
void printTree(node* nod){
	if (nod == NULL)
		return;
	
	printTree(nod->left);
	for (int i = 0; i < nod->size; i++)
		cout << "   ";
	cout << "(" << nod->data << "," << nod->size << ")";
	for (int i = 0; i < nod->size; i++)
		cout << "   ";
	cout << '\n';
	printTree(nod->right);
}
int v[10000];

void FillArray() {
	for (int i = 0; i < n; i++)
		v[i] = i + 1;
}
int main(){
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
	n = 11;
	srand(time(NULL));
	node *root = BuildTree(arr, 0, n - 1);
	cout << "Traversal of constructed BST \n";
	printTree(root);
	for (int i = 0; i < 3; i++) {
		int key = rand() % n + 1;
		cout << "-----------------------------------------------------\n";
		if(key == 1)
			cout << "| The " << key << "-st smallest element is going to be deleted! |\n";
		else
			if(key == 2)
				cout << "| The " << key << "-nd smallest element is going to be deleted! |\n";
			else
				if(key == 3)
					cout << "| The " << key << "-rd smallest element is going to be deleted! |\n";
				else
					cout << "| The " << key << "-th smallest element is going to be deleted! |\n";
		cout << "-----------------------------------------------------\n";
		root = OS_Delete(root, OS_Select(root, key)->data);
		n--;
		printTree(root);
		cout << '\n';
	}
	cout << "The program is going to sleep for 15 seconds such that you can see the pretty-print!\n";
	Sleep(15000);
	for (n = 100; n <= 10000; n += 100) {
		assignB = compareB = assignD = compareD = assignS = compareS = 0;
		for (int i = 0; i < 5; i++) {
			FillArray();
			node *root = BuildTree(v, 0, n - 1);
			for (int j = 0; j < n; j++) {
				int key = rand() % (n - j) + 1;
				node* val = OS_Select(root, key);
				cout << j << ": The " << key << "-th smallest element is going to be deleted!\n";
				root = OS_Delete(root, val->data);
			}
			cout << '\n';
		}
		profiler.countOperation("Build", n, assignB / 5 + compareB / 5);
		profiler.countOperation("Select", n, assignS / 5 + compareS / 5);
		profiler.countOperation("Delete", n, assignD / 5 + compareD / 5);
		profiler.countOperation("TotalNoOfOperations", n, (assignB + assignS + assignD) / 5 + (compareB + compareS + compareD) / 5);
	}
	profiler.createGroup("ManagementOpComparison", "Build", "Select", "Delete");
	profiler.showReport();
	///Sleep(100000);
	return 0;
}
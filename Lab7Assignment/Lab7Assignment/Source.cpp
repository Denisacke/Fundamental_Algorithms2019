/**
* @author Flueran Robert-Denis
* @group 30423
* Specification of the problem:	We are required to implement correctly and efficiently linear time transformations between
								three different representations for a multi-way tree: R1 (parent representation), R2 (multi-way representation),
								R3 (binary tree representation, along with a pretty print)


* Personal interpretation: 		In order to make the transformations, I've made use of two structures. For the first transformation (from parent
								to multi-way representation), I've used the "node" structures, that has a field of data and a vector of nodes, in
								which children of the node are stored. To make the transformation, I also needed an array of nodes (createdNodes),
								as additional memory, in which I push back the children nodes accordingly in O(n) time, because I couldn't have
								done the transformations with individual instances of nodes..I needed an array of structures in which I allocate 
								memory for all the nodes (the no. of nodes is defined by global variable n). It is O(n) because I traverse the
								parentVector only once, with a for loop from 0 to n - 1 and I push back some stuff.

								To make the transformation from multi-way representation to binary tree representation, I needed another structure,
								called BNode (that has data, the leftmost child of a node and its sibling) and an array of these structures, but what
								I also needed was the already created array from the first transformation, since I could make use of the already
								created links from it (I knew which nodes had children, so I used the first array of structures to link a node to
								its first child in the vector of nodes and used a for loop to link the children of the current node between them).
								Even if I had the first array, I also needed an array for the new structure in which I allocate memory for each
								node and I make the necessary links, because, again, it is quite hard to make individual variables to work with,
								and it's much easier to access the information stored in a node from an array.

								I may have used nested for loops, but the sub-for loop is rarely being executed and it doesn't have to go through
								that many elements..In the cases where the nodes are leaves, only a comparison is being made (if clause)..so the
								time complexity would still be around O(n).

								I have indexed the createdNodes and createdB array from 1 because, in the documentation, there is no node 0..
								it starts from node 1, and it was easier for me to index it like that..
**/

#include <iostream>
#include <vector>
#include <conio.h>
#include "Profiler.h"
using namespace std;
int parentVector[10001] = { 2, 7, 5, 2, 7, 7, -1, 5, 2 };
int n;
struct node{
	int data;
	vector<node*> children;
};

struct BNode {
	int data;
	BNode *child;
	BNode *sibling;
};
node* newNode(int data) {
	node* nod = new node();
	nod->data = data;
	return nod;
}

BNode* newBNode(int data) {
	BNode *nod = new BNode();
	nod->data = data;
	nod->child = NULL;
	nod->sibling = NULL;
	return nod;
}
node *root;
node *createdNodes[10001];
BNode *createdB[10001];
BNode *bRoot;
void createMWay(){
	for (int i = 0; i < n; i++)
		createdNodes[i + 1] = newNode(i + 1);

	for (int i = 0; i < n; i++)
		if(parentVector[i] != -1)
			createdNodes[parentVector[i]]->children.push_back(createdNodes[i + 1]);

}

void createBinary() {
	for (int i = 0; i < n; i++)
		createdB[i + 1] = newBNode(i + 1);

	for(int i = 0; i < n; i++)
		if (createdNodes[i + 1]->children.size()) {
			createdB[i + 1]->child = createdB[createdNodes[i + 1]->children[0]->data];
			for (int j = 0; j < createdNodes[i + 1]->children.size() - 1; j++)
				createdB[createdNodes[i + 1]->children[j]->data]->sibling = createdB[createdNodes[i + 1]->children[j + 1]->data];
		}
}
/*void PrintMWay(node* root, int size) {
	for (int i = 0; i < 3 * size; i++)
		cout << " ";
	cout << root->data << '\n';
	for (int i = 0; i < root->children.size(); i++)
		PrintMWay(root->children[i], size + 1);
	/*cout << "The root is: " << root->data << "and its children are: ";
	for (int j = 0; j < root->children.size(); j++)
		cout << root->children[j]->data << " ";
}*/
void PrintBinary(BNode *root, int size) {
	for (int i = 0; i < 2 * size; i++)
		cout << " ";
	cout << root->data << '\n';
	if (root->child != NULL)
		PrintBinary(root->child, size + 1);
	if (root->sibling != NULL)
		PrintBinary(root->sibling, size);

}
int main(){

	n = 9;
	cout << "Parent Representation of the Multi-way Tree\n";
	for (int i = 0; i < n; i++)
		cout << parentVector[i] << " ";
	cout << '\n';
	createMWay();
	/*for (int i = 0; i < n; i++)
		if (parentVector[i] == -1)
			root = createdNodes[i + 1];*/
	cout << "\nMulti-Way Representation\n\n";
	for (int i = 0; i < n; i++) {
		if (createdNodes[i + 1]->children.size()) {
			if (parentVector[i] != -1)
				cout << "The children of node " << i + 1 << " are: ";
			else
				cout << "The children of the root are: ";
			for (int j = 0; j < createdNodes[i + 1]->children.size(); j++)
				cout << createdNodes[i + 1]->children[j]->data << " ";
			cout << '\n';
		}
		else
			cout << i + 1 << " is a leaf\n";
	}
	cout << "\nBinary representation of a multi-way tree\n";
	createBinary();
	for (int i = 0; i < n; i++)
		if (parentVector[i] == -1)
			bRoot = createdB[i + 1];
	PrintBinary(bRoot, 0);
	_getch();
	///Sleep(100000);
	return 0;
}
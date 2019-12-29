/**
* @author Flueran Robert-Denis
* @group 30423
* Specification of the problem:	We are required to implement correctly and efficiently the base operations for disjoint set
								and the Kruskal’s algorithm using disjoint sets

* Personal interpretation: 		In order to solve the tasks, I've made use of the functions Make-Set, Find-Set and Link from Cormen and I have
								also created 3 structs(or classes, but only with public fields), one for a node, one for an edge and one for an
								entire graph

								I've made a selection menu, such that you can choose between the demo for disjoint sets, demo for Kruskal and
								the actual Profiler stuff. At 1. I've made 5 sets of 2 elements each and printed the parents, along with their 
								ranks

								At 2. I've hardcoded as input the input graph from geeksforgeeks on this subject, to make sure that my output
								was correct (the same as their output).

								At 3. I've counted the no. of operations for Make-Set, Find-Set and Link and used Kruskal for a random graph.
								I have made sure that the graph is CONNECTED by connecting one node to the next one and so one (edge between
								node 1 and 2, edge between 2 and 3 and so on). For the other 3n + 1 edges, I have generated some random edges
								with random weights and made sure they weren't already existing in the graph.

								The function that counts the number of operations is LINEAR, as well as all the methods for the disjoint sets
								taken separately (Make-Set, Find-Set and Link). I have ignored counting of the sorting of the edges when 
								calculating the complexity of Kruskal algorithm, so my Profiler plot from 100 to 10000 show O(E * log V) time
								complexity (sorting of the edges would add O(E * log E) complexity to that), where E represents the number of
								Edges in the graph and V represents the number of Vertices.

								Find-Set seems to take the largest number of operations out of the three. Make-Set takes the least amount of
								operations (it's O(n)..it takes exactly 2*n operations).
*/
#include <iostream> 
#include <conio.h>
#include "Profiler.h"
#include <random>
#include <ctime>
using namespace std;
Profiler profiler("Lab8");
class node{
public:
	int data;
	node *parent;
	int rank;
};
class Edge{
public:
	int src, dest, weight;
};

int n;
int makeOp, findOp, linkOp;
class Graph{
public:

	int V, E;
	Edge* edge;
};
int freq[40000];

Graph* createGraph(int V, int E){
	Graph* graph = new Graph();
	graph->V = V;
	graph->E = E;

    graph->edge = new Edge[E * sizeof(Edge)];

	return graph;
}

Graph* graph;
node* nodes[100];
node* vertices[10001];
node* newNode(int data) {
	node* nod = new node();
	nod->data = data;
	nod->parent = nod;
	nod->rank = 0; 
	return nod;
}

void MakeSet(node *x) {
	makeOp += 2;
	x->rank = 0;
	x->parent = x;
}
node* FindSet(node *x){
	findOp++;
	if (x != x->parent) {
		findOp++;
		x->parent = FindSet(x->parent);
	}
		
	return x->parent;
}

void Link(node *x, node *y){
	linkOp++;
	if (x->rank > y->rank) {
		linkOp++;
		y->parent = x;
	}
	else{
		linkOp += 2;
		x->parent = y;
		if (x->rank == y->rank)
			y->rank++;
	}
	
}

void Union(node *x, node *y){
	Link(FindSet(x), FindSet(y));
}

void sortEdges(int n, Edge v[]) {
	int pos;
	for (int i = 0; i < n - 1; i++) {
		for(int j = i + 1; j < n; j++)
			if (v[i].weight > v[j].weight) {
				Edge aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}

	}

}

void Kruskal(Graph* graph) {
	int V = graph->V;
	int e = 0;
	Edge edges[10001];
	
	for (int i = 0; i < V; i++) 
		MakeSet(vertices[i]);
		
	sortEdges(graph->E, graph->edge);
	for (int i = 0; i < graph->E; i++)
		if (FindSet(vertices[graph->edge[i].src]) != FindSet(vertices[graph->edge[i].dest])) {
			edges[e++] = graph->edge[i];
			Union(vertices[graph->edge[i].src], vertices[graph->edge[i].dest]);
		}
	cout << "Minimum Spanning Tree\n";
	for (int i = 0; i < e; i++)
		cout << edges[i].src << " " << edges[i].dest << " = " << edges[i].weight << '\n';

}
int find(int parent[], int i){
	if (parent[i] == -1)
		return i;
	return find(parent, parent[i]);
}

/*void Union(int parent[], int x, int y){
	int xset = find(parent, x);
	int yset = find(parent, y);
	if (xset != yset){
		parent[xset] = yset;
	}
}

int isCycle(Graph* graph){
	
	int *parent = new int[graph->V * sizeof(int)];
	memset(parent, -1, sizeof(int) * graph->V);

	
	for (int i = 0; i < graph->E; ++i){
		int x = find(parent, graph->edge[i].src);
		int y = find(parent, graph->edge[i].dest);

		if (x == y)
			return 1;

		Union(parent, x, y);
	}
	return 0;
}*/


int main(){
	srand(time(NULL));
	int x;
	cout << "Choose from one of the three options:\n1.Disjoint Demo\n2.Kruskal Demo\n3.Profiler stuff\n";
	cin >> x;
	n = 10;
	if (x == 1) {
		for (int i = 0; i < n; i++)
			nodes[i] = newNode(i);
		for (int i = 0; i < n; i++)
			MakeSet(nodes[i]);
		for (int i = 0; i < n; i += 2) {
			cout << i << " has been linked with " << i + 1 << '\n';
			Union(nodes[i], nodes[i + 1]);
			///cout << "The node " << i + 1 << " belongs to the set: " << FindSet(nodes[i + 1])->data << " and has rank " << nodes[i + 1]->rank;
			///cout << '\n';
		}
		for (int i = 0; i < n; i++) {
			cout << "The node " << i << " belongs to the set with the root: " << FindSet(nodes[i])->data << " and has rank " << nodes[i]->rank;
			cout << '\n';
		}
		///free(nodes);
		
	}
	
	
	else
		if (x == 2) {
			graph = createGraph(4, 5);
			for (int i = 0; i < 4; i++)
				vertices[i] = newNode(i);
			graph->edge[0].src = 0;
			graph->edge[0].dest = 1;
			graph->edge[0].weight = 10;

			graph->edge[1].src = 0;
			graph->edge[1].dest = 2;
			graph->edge[1].weight = 6;
 
			graph->edge[2].src = 0;
			graph->edge[2].dest = 3;
			graph->edge[2].weight = 5;
 
			graph->edge[3].src = 1;
			graph->edge[3].dest = 3;
			graph->edge[3].weight = 15;

			graph->edge[4].src = 2;
			graph->edge[4].dest = 3;
			graph->edge[4].weight = 4;
			cout << "The edges of the hardcoded graph are:\n";
			for (int i = 0; i < 5; i++)
				cout << graph->edge[i].src << " " << graph->edge[i].dest << " = " << graph->edge[i].weight << '\n';
			Kruskal(graph);

		}
	
		else
			if(x == 3){
				for (n = 100; n <= 10000; n += 100) {
					findOp = linkOp = makeOp = 0;
					graph = createGraph(n, n * 4);
					int src[40001];
					int dest[40001];
					int weight[40001];
					for (int i = 0; i < n + 1; i++)
						vertices[i] = newNode(i);
					FillRandomArray(src, 3 * n + 1, 1, n, false, 0);
					FillRandomArray(dest, 3 * n + 1, 1, n, false, 0);
					FillRandomArray(weight, 3 * n + 1, 1, 100, false, 0);
					int e = 0;
					for (int i = 0; i < n - 1; i++) {
						graph->edge[i].src = i;
						graph->edge[i].dest = i + 1;
						graph->edge[i].weight = rand() % 100 + 1;
					}
					e = n - 1;
					for (int i = n - 1; i < n * 4; i++) {
						bool OK = 1;
						for(int j = 0; j < e; j++)
							if ((src[i] == graph->edge[j].src && dest[i] == graph->edge[j].dest) || (src[i] == graph->edge[j].dest &&
								dest[i] == graph->edge[j].src)) {
								OK = 0;
								break;
							}
						if (OK) {
							graph->edge[e].src = src[i];
							graph->edge[e].dest = dest[i];
							graph->edge[e].weight = weight[i];
							e++;
						}
					}
					graph->E = e;
					Kruskal(graph);
					profiler.countOperation("MakeOp", n, makeOp);
					profiler.countOperation("LinkOp", n, linkOp);
					profiler.countOperation("FindOp", n, findOp);
					profiler.countOperation("SumOps", n, makeOp + linkOp + findOp);
					///cout << n << " " << e << '\n';
				}

		}
	profiler.createGroup("OpComparison", "MakeOp", "LinkOp", "FindOp");
	if (x == 3) {
		profiler.showReport();
		cout << "Done!\n";
	}
		
	
	_getch();
	return 0;
}
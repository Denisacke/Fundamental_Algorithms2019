/**
* @author Flueran Robert-Denis
* @group 30423
* Specification of the problem:	We are required to implement correctly and efficiently the Depth-First Search (DFS)
								graph algorithm. We are also required to implement the Tarjan algorithm and topological sorting

* Personal interpretation: 		In order to perform the algorithm, I've made a class (which could very well be changed into a struct,
								since I only have public fields), called Graph, which has as field the no. of vertices, adjacency
								list, a stack, a constructor and methods for adding an edge, performing DFS on the graph, 
								performing Tarjan's algorithm and topological sorting.

								For the demo, I've hardcoded a graph in main() and applied DFS, Tarjan and Topological Sorting to
								it. I've printed the adjacency lists, the DFS, the SCC (strongly connected components) and the 
								nodes sorted in topological order.

								DFS has O(V + E) time complexity, as it can be seen from the Profiler plot. It's a linear algorithm.

								For the DFS algorithm, I have used a "visited" array, where I mark each node as I visit 'em and make
								sure I don't visit a node more than once.

								For the Topological Sort, I've applied DFS and put the nodes on a stack such that, when I am done
								with the DFS and start popping from the stack, I get the elements in topological order. Now, there's
								a CATCH..since it uses DFS (so it always visits nodes that haven't already been visited), it can
							    output a result even from a graph that has cycles, so it is not quite right to prove the 
								correctness of both Tarjan and Topological Sort from a single graph. That's why I've hardcoded
								another graph (an acyclic one, this time), such that Topological Sort can work properly. In this
								acyclic graph, Tarjan's algorithm can't find SCCs with more than one node.
								As a result, the acyclic graph should have V strongly connected components, where V = no of vertices.
								Sooo this is how I've shown that both Tarjan and Topological Sort work fine.

								For Tarjan's algorithm, I've made use of two arrays (disc and low) and a stack. Disc[i] represents
								the time stamp when node i has been discovered for the first time. Low[i] represents the lowest
								node that can be reached from node i by applying DFS.



*/

#include <iostream>
#include <conio.h>
#include "Profiler.h"
#include <list>
#include <stack>
#include <random>
#include <ctime>
using namespace std;
Profiler profiler("Lab10");
class node {
public:
	int data;
	node *parent;
	int rank;
};
bool visited[500];
int Op;
node* newNode(int data) {
	node* nod = new node();
	nod->data = data;
	nod->parent = nod;
	nod->rank = 0;
	return nod;
}

class Graph{
	
public:
	int V;
	list<int> *adj;

	stack<int> st;
	Graph(int V);  
	void addEdge(int v, int w);
	void SCC1(int u, int disc[], int low[], bool stackMember[]);
	void SCC();
	void DFS(int v);
	void topologicalSort();
	void topDFS(int v);
};

void emptyVisited() {
	for (int i = 0; i < 500; i++)
		visited[i] = 0;
}
Graph::Graph(int V){
	this->V = V;
	adj = new list<int>[V];
}

void Graph::addEdge(int v, int w){
	adj[v].push_back(w); 
}

void Graph::DFS(int v){
	
	visited[v] = true;
	cout << v << " ";
	Op++;
	
	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i) {
		Op++;
		if (!visited[*i])
			DFS(*i);
	}
		
}
void Graph::topDFS(int v) {
	visited[v] = true;
	//cout << v << " ";


	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
		if (!visited[*i])
			topDFS(*i);
	st.push(v);
}
void Graph::topologicalSort() {
	emptyVisited();
	for (int i = 0; i < V; i++)
		if (!visited[i])
			topDFS(i);
	while (!st.empty()) {
		cout << st.top() << " ";
		st.pop();
	}
}

void printAdjacencyList(Graph g) {
	for (int i = 0; i < g.V; i++) {
		list<int>::iterator it;
		cout << "Node " << i << ": ";
		for (it = g.adj[i].begin(); it != g.adj[i].end(); ++it)
			cout << *it << " ";
		cout << '\n';
	}
}

void Graph::SCC1(int u, int disc[], int low[], bool stackMember[]){
	
	static int time = 0;

	disc[u] = low[u] = ++time;
	st.push(u);
	stackMember[u] = true;

	list<int>::iterator i;
	for (i = adj[u].begin(); i != adj[u].end(); ++i){
		

		if (disc[*i] == -1){
			SCC1(*i, disc, low, stackMember);

			low[u] = min(low[u], low[*i]);
		}
		else
			if (stackMember[*i] == true)
				low[u] = min(low[u], disc[*i]);
	}

	int w = 0; 
	if (low[u] == disc[u]){
		while (st.top() != u){
			w = (int)st.top();
			cout << w << " ";
			stackMember[w] = false;
			st.pop();
		}
		w = (int)st.top();
		cout << w << "\n";
		stackMember[w] = false;
		st.pop();
	}
}

void Graph::SCC(){
	int *disc = new int[V];
	int *low = new int[V];
	bool *stackMember = new bool[V];
	

	
	for(int i = 0; i < V; i++){
		disc[i] = -1;
		low[i] = -1;
		stackMember[i] = false;
	}

	for (int i = 0; i < V; i++)
		if (disc[i] == -1)
			SCC1(i, disc, low, stackMember);
}



int main(){
	srand(time(NULL));
	emptyVisited();
	Graph g(6);
	g.addEdge(0, 1);
	g.addEdge(1, 2);
	g.addEdge(2, 0);
	g.addEdge(2, 4);
	g.addEdge(4, 5);
	g.addEdge(5, 4);
	g.addEdge(1, 4);
	g.addEdge(1, 3);
	g.addEdge(3, 5);
	cout << "Following is Depth First Traversal"
		" (starting from vertex 0) \n";
	g.DFS(0);

	cout << "\nThis represents the Topological Sort for the demo graph \n";
	g.topologicalSort();
	cout << "\nTopological Sort tries to compute an order for the nodes in the graph, but it can't do it properly, since the graph has cycles";
	cout << "\nTarjan's Algorithm\n";
	g.SCC();
	cout << "\nAdjacency Lists for the nodes in the demo graph\n";
	printAdjacencyList(g);
	emptyVisited();
	cout << "\nHere's another graph..an acyclic, directed one\n";
	Graph g1(6);
	g1.addEdge(0, 1);
	g1.addEdge(0, 2);
	g1.addEdge(0, 3);
	g1.addEdge(1, 4);
	g1.addEdge(2, 5);
	g1.addEdge(3, 5);
	g1.addEdge(4, 5);
	cout << "\nThis represents the Topological Sort for the demo graph \n";
	g1.topologicalSort();
	cout << "\nTarjan's Algorithm\nAs expected, it shows that there are 6 SCC, each with a single node\n";
	g1.SCC();
	cout << "\nAdjacency Lists for the nodes in the demo graph\n";
	printAdjacencyList(g1);
	cout << "\nInput anything in order to start the Profiler Stuff\n";
	_getch();
	int componentNumber;
	for (int e = 1000; e <= 5000; e += 100) {
		Graph graph(100);
		componentNumber = 0;
		emptyVisited();
		Op = 0;
		int k = 0;
		while (k < e) {
			int src = rand() % 100;
			int dest = rand() % 100;
			list<int>::iterator it;
			bool OK = 1;
			for (it = graph.adj[src].begin(); it != graph.adj[src].end(); ++it) {
				if (*it == dest) {
					OK = 0;
					break;
				}
			}
			/*if (OK) {
				for (it = graph.adj[dest].begin(); it != graph.adj[dest].end(); ++it) {
					if (*it == src) {
						OK = 0;
						break;
					}
				}
			}*/

			if (OK) {
				k++;
				graph.addEdge(src, dest);
			}
		}
		for (int i = 0; i < 100; i++)
			if (!visited[i]) {
				componentNumber++;
				cout << "Component " << componentNumber << ": root is " << i << '\n';
				graph.DFS(i);
				cout << '\n';
			}

		profiler.countOperation("DFS_Op_E_Varies", e, Op);
	}
	cout << "\nFirst part is done! Input anything for the part where the number of vertices varies\n";
	_getch();
	int e = 9000;
	for (int v = 200; v <= 300; v += 10) {
		Graph graph(v);
		emptyVisited();
		componentNumber = 0;
		Op = 0;
		int k = 0;
		while (k < e) {
			int src = rand() % v;
			int dest = rand() % v;

			list<int>::iterator it;
			bool OK = 1;

			for (it = graph.adj[src].begin(); it != graph.adj[src].end(); ++it) {
				if (*it == dest) {
					OK = 0;
					break;
				}
			}
			/*if (OK) {
				for (it = graph.adj[dest].begin(); it != graph.adj[dest].end(); ++it) {
					if (*it == src) {
						OK = 0;
						break;
					}
				}
			}*/
			if (OK) {
				k++;
				///cout << k << " Edge added\n";
				graph.addEdge(src, dest);
			}
		}
		for (int i = 0; i < 100; i++)
			if (!visited[i]) {
				componentNumber++;
				cout << "Component " << componentNumber << ": root is " << i << '\n';
				graph.DFS(i);

			}


		profiler.countOperation("DFS_Op_V_Varies", v, Op);
	}
	profiler.showReport();
	cout << "\nAll done!";
	_getch();
	return 0;
}
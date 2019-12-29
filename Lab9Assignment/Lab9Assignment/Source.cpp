#include <iostream> 
#include <list> 
#include "Profiler.h"
#include <conio.h>
#include <random>
#include <ctime>
using namespace std;
Profiler profiler("Lab9");
int Op;
class Graph {

public:
	int V;

	list<int> *adj;
	Graph(int V);


	void addEdge(int v, int w);

	void BFS(int s);
};

Graph::Graph(int V) {
	this->V = V;
	adj = new list<int>[V];
}

void Graph::addEdge(int v, int w) {
	adj[v].push_back(w);
}

void Graph::BFS(int s) {

	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;
	Op += V;
	list<int> queue;

	visited[s] = true;
	queue.push_back(s);
	Op += 2;

	list<int>::iterator i;
	while (!queue.empty()) {
		Op++;
		Op++;
		s = queue.front();
		cout << s << " ";
		queue.pop_front();
		Op += queue.size() - 1;
		for (i = adj[s].begin(); i != adj[s].end(); ++i) {
			Op++;
			if (!visited[*i]) {
				Op += 2;
				visited[*i] = true;
				queue.push_back(*i);
			}
		}
	}
}


int main() {
	srand(time(NULL));
	Graph g(4);
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 2);
	g.addEdge(2, 0);
	g.addEdge(2, 3);
	g.addEdge(3, 3);

	cout << "Following is Breadth First Traversal "
		<< "(starting from vertex 2) \n";
	g.BFS(2);
	cout << "\nInput anything in order to start the Profiler Stuff\n";
	_getch();

	for (int e = 1000; e <= 5000; e += 100) {
		Graph graph(100);
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
			if (OK) {
				for (it = graph.adj[dest].begin(); it != graph.adj[dest].end(); ++it) {
					if (*it == src) {
						OK = 0;
						break;
					}
				}
			}

			if (OK) {
				k++;
				graph.addEdge(src, dest);
			}
		}
		graph.BFS(1);
		profiler.countOperation("BFS_Op_E_Varies", e, Op);
	}
	/*int e = 9000;
	for (int v = 100; v <= 200; v += 10) {
		Graph graph(v);

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
			if (OK) {
				for (it = graph.adj[dest].begin(); it != graph.adj[dest].end(); ++it) {
					if (*it == src) {
						OK = 0;
						break;
					}
				}
			}

			if (OK) {
				k++;
				graph.addEdge(src, dest);
			}
		}
		cout << "I got here!\n";
		graph.BFS(1);
		cout << "I got here!\n";
		profiler.countOperation("BFS_Op_V_Varies", v, Op);
	}*/
	profiler.showReport();
	_getch();
	return 0;
}
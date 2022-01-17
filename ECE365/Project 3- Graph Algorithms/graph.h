// Joongyeon Cho
// ECE365
// Project 3
// graph.h

#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <climits>
#include "fstream"
#include "heap.h"

using namespace std;
class graph {
public:
	graph();
	void loadFile(ifstream& lFile);
	void dijkstra(const string&);
	void print(ofstream& outFile);

private:
	void insert(const std::string& id1, const std::string& id2, int cost);

	struct Edge {
		Edge(const string destination, int cost) :destination(destination), cost(cost) {}
		string destination;
		int cost;
	};

	struct Node {
		Node(const string id) : id(id) {
			dValue = INT_MAX;
			visited = false;
		}
		std::string id;
		int dValue;
		bool visited;
		std::list<Edge> adjacencyList; 
		std::list<string> path;
	};

	int filled;
	std::list<Node*> nodeList;
	hashTable* nodes;
};
#endif 
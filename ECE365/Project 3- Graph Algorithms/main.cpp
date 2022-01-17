#include <iostream>
#include <chrono>
#include "graph.h"

using namespace std;

int main() {
	string graphFile, startingVertex, outFile;
	ifstream inputFile;
	ofstream outputFile;
	graph myGraph;
	cout << "Enter name of graph file: ";
	cin >> graphFile;
	inputFile.open(graphFile, ifstream::in);
	myGraph.loadFile(inputFile);
	cout << "Enter name of starting vertex: ";
	cin >> startingVertex;
	clock_t start = clock();
	myGraph.dijkstra(startingVertex);
	clock_t end = clock();
	cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << (float)(end - start) / CLOCKS_PER_SEC << "s";
	cout << "\nEnter the name of output file: ";
	cin >> outFile;
	outputFile.open(outFile, ofstream::out);
	myGraph.print(outputFile);
	return 0;
}
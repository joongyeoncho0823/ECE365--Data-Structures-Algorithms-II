#include "graph.h"

graph::graph() {
	nodes = new hashTable(10000);
	filled = 0;
}

void graph::insert(const string& id1, const string& id2, int cost) {

	Node* node1; 
	Node* node2;

	if (!nodes->contains(id1)) {
		node1 = new Node(id1);
		nodes->insert(id1, node1);
		nodeList.push_back(node1);
		filled++;
	}
	else {
		node1 = (Node*)nodes->getPointer(id1);
	}
	if (!nodes->contains(id2)) {
		node2 = new Node(id2);
		nodes->insert(id2, node2);
		nodeList.push_back(node2);
		filled++;
	}
	else {
		node2 = (Node*)nodes->getPointer(id2);
	}

	Edge edge(id2, cost);
	node1->adjacencyList.push_back(edge);
}

void graph::dijkstra(const string& startNode) {

	heap thisHeap(filled);

	Node* start = (Node*)(nodes->getPointer(startNode));
	
	int totalWeight; 
	start->dValue = 0;
	start->path.push_back(startNode);
	thisHeap.insert(startNode, start->dValue, start);
	
	for (list<Node*>::iterator it = nodeList.begin(); it != nodeList.end(); it++) {
		if((*it)->id != startNode)
			thisHeap.insert((*it)->id, (*it)->dValue, *it);
	}

	Node* tmp = nullptr;
	while (!thisHeap.deleteMin(nullptr, nullptr, &tmp)) {
		tmp->visited = true;
		for(list<Edge>::iterator iter = tmp->adjacencyList.begin(); iter != tmp->adjacencyList.end(); iter++){
			Node* n2 = (Node*)(nodes->getPointer(iter->destination));
			totalWeight = iter->cost + tmp->dValue;
			if ((totalWeight < n2->dValue) && !n2->visited) {
				n2->path.assign(tmp->path.begin(), tmp->path.end());
				n2->path.push_back(n2->id);

				n2->dValue = totalWeight;
				thisHeap.setKey(n2->id, n2->dValue);
			}
		}
	}

}
void graph::loadFile(ifstream& lFile) {
	string n1, n2;
	int cost; 

	while (lFile >> n1 >> n2 >> cost) {
		insert(n1, n2, cost);
	}
	
	lFile.close();
}

void graph::print(ofstream & outFile) {
	for (list<Node*>::iterator iter = nodeList.begin(); iter != nodeList.end(); iter++) {
		outFile << (*iter)->id << ": ";
		if ((*iter)->dValue == INT_MAX) {
			outFile << "NO PATH\n";
		}
		else {
			outFile << (*iter)->dValue << " [";
			for (list<string>::const_iterator sIter = (*iter)->path.begin(); sIter != prev((*iter)->path.end())	; sIter++) {

				outFile << *sIter << ", ";
			}
			outFile << (*iter)->path.back() << "]\n";
		}
	}

	outFile.close();
}
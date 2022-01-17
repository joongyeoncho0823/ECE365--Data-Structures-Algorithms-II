// Joongyeon Cho
// ECE365
// Project 2
// heap.h

#ifndef _HEAP_H
#define _HEAP_H

#include <vector>

#include "hash.h"

class heap
{
public:
	// The constructor initializes the heap.
	heap(int capacity = 0);

	// Insert the goven string and key to the heap.
	int insert(const std::string& id, int key, void* pv = nullptr);

	// Change the key of an existing entry.
	int setKey(const std::string& id, int key);

	// Remove top item from heap
	int deleteMin(std::string* pId = nullptr, int* pKey = nullptr, void* ppData = nullptr);

	// Remove item from heap.
	int remove(const std::string& id, int* pKey = nullptr, void* ppData = nullptr);

private:
	class node
	{ // An inner class within heap
	public:
		std::string id; // The id of this node
		int key;        // The key of this node
		void* pData;    // A pointer to the actual data
	};

	std::vector<node> data;
	hashTable mapping;

	int capacity;
	int filled;
	void percolateUp(int posCur);
	void percolateDown(int posCur);
	int getPos(node* pn);
};

#endif //_HEAP_H
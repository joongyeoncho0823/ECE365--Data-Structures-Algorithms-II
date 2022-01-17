// Joongyeon Cho
// ECE365
// Project 2
// heap.cpp

#include "heap.h"
#include <string>
#include <iostream>

heap::heap(int capacity) : mapping(capacity * 2)
{
	data.resize(capacity + 1);
	this->capacity = capacity;
	filled = 0;
}

int heap::insert(const std::string& id, int key, void* pv)
{
	//heap is full
	if (capacity == filled)
		return 1;

	//string already exists
	else if (mapping.contains(id))
		return 2;

	//insert new id
	else
	{
		int pos = ++filled; // filled +1 to ++filled and filled++ taken out at bottom;; might be Source of Error
		data[pos].id = id;
		data[pos].key = key;
		data[pos].pData = pv;
		mapping.insert(id, &data[pos]);
		percolateUp(pos);
		return 0;
	}
}

int heap::setKey(const std::string& id, int key)
{
	bool b;
	node* pnode = static_cast<node*>(mapping.getPointer(id, &b));

	if (b == false)
		return 1;
	else
	{
		int tkey = pnode->key;
		pnode->key = key;
		int pos = getPos(pnode);
		if (key > tkey)
			percolateDown(pos);
		else if (key < tkey)
			percolateUp(pos);
		return 0;
	}
}

int heap::deleteMin(std::string* pId, int* pKey, void* ppData)
{
	if (filled == 0)
		return 1;

	else
	{
		node min = data[1];
		if (pId)
			*pId = min.id;
		if (pKey)
			*pKey = min.key;
		if (ppData)
			*(static_cast<void**>(ppData)) = data[1].pData;

		mapping.remove(min.id);
		data[1] = data[filled--];
		data[filled + 1] = node();
		percolateDown(1);

		return 0;
	}
}
//not done
int heap::remove(const std::string& id, int* pKey, void* ppData)
{
	bool b;
	node* pnode = static_cast<node*>(mapping.getPointer(id, &b));

	if (b == false)
		return 1;
	else
	{
		if (pKey)
			*pKey = pnode->key;
		if (ppData)
			*(static_cast<void**>(ppData)) = pnode->pData;

		mapping.remove(id);
		int tkey = pnode->key;
		*pnode = data[filled--];
		//data[filled + 1] = node();
		int newKey = pnode->key;

		int pos = getPos(pnode);
		if (tkey <= newKey)
			percolateDown(pos);
		else if (tkey > newKey)
			percolateUp(pos);
		return 0;
	}
}

void heap::percolateUp(int posCur)
{
	node temp = data[posCur];
	while (temp.key < data[posCur / 2].key && posCur > 1) // changed
	{
		data[posCur] = data[posCur / 2];
		mapping.setPointer(data[posCur / 2].id, &data[posCur]);
		posCur /= 2;
	}

	data[posCur] = temp;
	mapping.setPointer(data[posCur].id, &data[posCur]);
	data[0] = node();
}

void heap::percolateDown(int posCur)
{
	int child;
	node temp = data[posCur];
	for (; posCur * 2 <= filled; posCur = child)
	{
		child = posCur * 2;

		if (child != filled && data[child + 1].key < data[child].key)
			child++;
		if (data[child].key < temp.key)
		{
			data[posCur] = data[child];
			mapping.setPointer(data[posCur].id, &data[posCur]);
		}
		else
			break;
	}
	data[posCur] = temp;
	mapping.setPointer(data[posCur].id, &data[posCur]);
	data[0] = node();
}

int heap::getPos(node* pn)
{
	int pos = pn - &data[0];
	return pos;
}
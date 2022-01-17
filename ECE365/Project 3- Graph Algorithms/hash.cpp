//Joongyeon Steven Cho
//ECE365
// Project_2: use heap and hash
//File: hash.cpp

#include "hash.h"
#include <iostream>

using namespace std;

unsigned int primes[] = { 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469 };
unsigned int size_primes = sizeof(primes) / sizeof(primes[0]);

hashTable::hashTable(int size)
{
	capacity = getPrime(size);
	filled = 0;
	data.resize(capacity);
}

int hashTable::insert(const string& key, void* pv)
{
	// key already exists in hash table
	if (contains(key))
		return 1;

	else
	{
		// rehash fails
		if ((filled + 1) > capacity / 2)
		{
			if (!rehash())
				return 2;
		}
		// success
		int hashVal = hash(key);
		while (data[hashVal].isOccupied == true && data[hashVal].isDeleted == false)
		{
			++hashVal %= capacity;
		}

		data[hashVal].isOccupied = true;
		data[hashVal].isDeleted = false;
		data[hashVal].key = key;
		data[hashVal].pv = pv;
		filled++;
		return 0;
	}
}

bool hashTable::contains(const string& key)
{
	return (findPos(key) >= 0) ? true : false;
}

void* hashTable::getPointer(const string& key, bool* b)
{
	// If the key does not exist in the hash table, return nullptr
	if (!contains(key))
	{
		if(b != nullptr)
			*b = false;
		return nullptr;
	}
	else
	{
		if (b != nullptr)
			*b = true;
		int pos = findPos(key);
		return data[pos].pv;
	}
}

int hashTable::setPointer(const string& key, void* pv)
{
	int hashVal = findPos(key);

	if (hashVal == -1)
		return 1;
	else
	{
		data[hashVal].pv = pv;
		return 0;
	}
}
// Delete the item with the specified key.
// Returns true on success,
// false if the specified key is not in the hash table.
bool hashTable::remove(const string& key)
{
	int hashVal = findPos(key);
	if (hashVal == -1)
		return false;
	data[hashVal].isDeleted = true;  // Changed
	return true;
}

// hash function from https://stackoverflow.com/questions/98153/whats-the-best-hashing-algorithm-to-use-on-a-stl-string-when-using-hash-map
int hashTable::hash(const string& key)
{
	unsigned int hashVal = 0;
	const char* s = key.c_str();
	while (*s)
	{
		hashVal = hashVal * 101 + *s++;
	}
	return hashVal % capacity;
}
// Search for an item with the specified key.
// Return the position if found, -1 otherwise.
int hashTable::findPos(const string& key)
{
	int hashVal = hash(key);
	while (data[hashVal].isOccupied == true)
	{
		if (data[hashVal].key == key && data[hashVal].isDeleted == true)
			return -1;
		else if (data[hashVal].key == key && data[hashVal].isDeleted == false)
			return hashVal;
		++hashVal %= capacity;
	}
	return -1;
}

bool hashTable::rehash()
{
	vector<hashItem> temp = data;
	for (unsigned int i = 0; i < size_primes; i++)
	{
		if (capacity == primes[6])
			return false;
		if (capacity == primes[i])
		{
			capacity = primes[i + 1];
			break;
		}
	}
	data.clear();
	data.resize(capacity);
	for (auto i : temp)
	{
		if ((i.isOccupied == true) && (i.isDeleted == false))
			insert(i.key, i.pv);
	}
	return true;
}

unsigned int hashTable::getPrime(int size)
{
	for (int i : primes)
		if ((size * 2) + 1 < i)
			return i;
	return primes[6];
}
#pragma once
/******************************************************************************** ******************************** HashTable Class ********************************* *********************************************************************************
* Author: (Hiren Rathod) (100%)
*
* This class serves as a hash table that provides a user with efficiency in insertion, removal, and searching.
* It contains several ADT functions to allow the user to experience optimal functionality with their data.
* In the real world, an emergency system would be benefitted by the use of a hash table due to the hash table's potential for speedy searches.
* In an ideal case, this hash table can return a value within the table in O(1) time.
* This hash table uses separate chaining as the collision resolution mechanism.
* To combat an O(n) traversal, this hash table uses a rehashing function to resize the table.
*****************
**** USAGE ***
*****************
* Declare an object of type HashTable, using template initialization.
* You may then call HashTable functions on the new HashTable object.
* ADT Functionalities:
- Add
- isEmpty
- Remove
- Empty
- Manipulate Data
- Get essential information about the data and the ADT itself
Keep in mind:
* It's advised to avoid repeatedly entering the same data. In order to preserve the search efficiency of the table, the table will resize itself but newly allocated memory becomes wasted if it is not used.
* Avoid attempts of removing or getting the number of operations used on data not present in the table.
*********************************************************************************************************************************************************************************************************************************************************/

#ifndef Hash_h
#define Hash_h

#include <iostream>
#include "List.h"

template<typename K, typename V>
class HashTable
{
private:
	//Pointer to array of linked lists
	List<V>* arr;
	//Size of table
	int size;
	//Num of items in the table
	int count;
	//Load factor with respect to the hash table
	double loadFactor;
	//key used for key/value pairs for better searching, encrypting, and handling of complex data types
	int cachedKey;
	//number of nodes that are chained on the linked list...non O(1) traversal;
	int offTable;
	/*
	* genAlg
	*
	* brief: Function that generates the modulo algorithm for an integer value
	*
	* param: item - integer value that will be stored in table
	*
	* returns: index that serves as a hash address
	*/
	int genAlg(int key) const;
	/*
	* genAlg
	*
	* brief: Function that generates the modulo algorithm for a double value
	*
	* param: item - double value that will be stored in table
	*
	* returns: index that serves as a hash address
	*/
	int genAlg(double key) const;
	/*
	* genAlg
	*
	* brief: Function that generates the modulo algorithm for a char value
	*
	* param: item - char value that will be stored in table
	*
	* returns: index that serves as a hash address
	*/
	int genAlg(char key) const;
	/*
	* genAlg
	*
	* brief: Function that generates the modulo algorithm/folding algorithm for a string value
	*
	* param: item - string value that will be stored in table
	*
	* returns: index that serves as a hash address
	*
	* note: Performs a specialized folding algorithm with each character of the string. genAlg function is replicated for all data types as modulo operations on string objects are not allowed.
	*/
	int genAlg(std::string key) const;
	/*
	* reHash
	*
	* brief: Function that performs rehashing when the number of nodes in the table exceed the table size.
	*/
	void reHash();
public:
	/*
	* HashTable
	*
	* brief: Default Constructor that initializes member attributes
	*/
	HashTable();
	/*
	* getSize
	*
	* brief: Function that returns the size of the table
	*
	* returns: size
	*/
	int getSize() const;
	/*
	* add
	*
	* brief: Function that adds an item/key to the table at a specific hash address
	*
	* param: item - value that will be stored in table
	*
	* returns: boolean value to represent success/failure
	*/
	bool add(const K& key); //If no value is passed, it is assumed the key is the value as well
	/*
	* add
	*
	* brief: Function that adds an item/key to the table at a specific hash address
	*
	* param: key - key/value pair for better searching and handling of complex data types, item - value that will be stored in table
	*
	* returns: boolean value to represent success/failure
	*/
	bool add(const K& key, const V& value);
	/*
	* remove
	*
	* brief: Function that removes an item/key from the table at a specific hash address
	*
	* param: item - value that will be removed from the table
	*
	* returns: boolean value to represent success/failure
	*/
	bool remove(const K& key);
	/*
	* remove
	*
	* brief: Function that removes an item/key from the table at a specific hash address
	*
	* param: key - key/value pair for better searching and handling of complex data types, item - value that will be removed from the table
	*
	* returns: boolean value to represent success/failure
	*/
	bool remove(const K& key, const V& value);
	/*
	* calcLoadFactor
	*
	* brief: Function that calculates and return the load factor of the table at any given time
	*
	* returns: loadFactor
	*/
	double calcLoadFactor() const;
	/*
	* getAddress
	*
	* brief: Wrapper function that calls the private genAlg functions as the data type of a key is determined
	*
	* param: item - value that will be stored in the table
	*
	* returns: valid hash address
	*/
	int getAddress(const K& key);
	/*
	* empty
	*
	* brief: Function that empties the hash table of all entries
	*/
	void empty();
	/*
	* isEmpty
	*
	* brief: Function that returns if the HashTable has any values
	*
	* returns: bool value representing if there are any values in the hash table
	*/
	bool isEmpty();
	/*
	* getCount
	*
	* brief: Function that returns the number of nodes present in the table.
	*
	* returns: count
	*/
	int getCount() const;
	/*
	* getOperations
	*
	* brief: Function that returns the number of traversals it takes to locate a passed item in the table.
	*
	* param: item - value within the table
	*
	* returns: number of traversals in a linked list
	*/
	int getOperations(const K& key);
	/*
	* getOperations
	*
	* brief: Function that returns the number of traversals it takes to locate a passed item in the table.
	*
	* param: key - key/value pair for better searching and handling of complex data types, item - value within the table
	*
	* returns: number of traversals in a linked list
	*/
	int getOperations(const K& key, const V& value);
	/*
	* getNextPrime
	*
	* brief: Function that returns the next available primre number for hash function use.
	*
	* returns: prime number
	*/
	int getNextPrime();
	/*
	* getOffTable
	*
	* brief: Function that returns nodes that aren't on a linked list with 1 node
	*
	* returns: offTable
	*/
	int getOffTable() const;
	/*
	* ~HashTable
	*
	* brief: Destructor that empties the array of linked lists and deletes the array
	*/
	~HashTable();
	//Friend Overloaded Insertion Operator for printing
	template <typename K, typename V>
	friend std::ostream& operator<<(std::ostream& os, const HashTable<K, V>& table);
};

template<typename K, typename V>
HashTable<K, V>::HashTable()
{
	//Member Variables initialized, size set to prime number 101
	size = 101;
	count = 0;
	arr = new List<V>[size];
	cachedKey = -1;
	offTable = 0;
}

template<typename K, typename V>
int HashTable<K, V>::getOperations(const K& key)
{
	//Finding index of item on table
	int index = getAddress(key);
	//Counts number of traversals at that index to find item
	int op = (arr + index)->getPos(key);
	if (op == -1)
		return -1;
	//Increments operations by one as the list begins at the 0th index
	return op + 1;
}

template<typename K, typename V>
int HashTable<K, V>::getOperations(const K& key, const V& value)
{
	cachedKey = key;
	//Finding index of item on table
	int index = getAddress(key);
	//Counts number of traversals at that index to find item
	int op = (arr + index)->getPos(value);
	if (op == -1)
		return 0;
	//Increments operations by one as the list begins at the 0th index
	return op + 1;
}

template<typename K, typename V>
int HashTable<K, V>::getSize() const
{
	//Size of table
	return size;
}

template<typename K, typename V>
int HashTable<K, V>::getCount() const
{
	//Number of nodes in table
	return count;
}

template<typename K, typename V>
double HashTable<K, V>::calcLoadFactor() const
{
	//Load Factor = table items / table size
	return ((double)count / size);
}

template<typename K, typename V>
bool HashTable<K, V>::add(const K& key)
{
	cachedKey = key;
	if (!(arr + getAddress(key))->isEmpty())
		offTable++;
	//Calls hash function and stores at beginning of the list at computed index
	(arr + getAddress(key))->insertFirst(key);
	//Increments number of nodes
	count++;
	//If number of nodes are greater than table size
	if (calcLoadFactor() > 1.0)
		reHash(); //Rehashing
	return true;
}

template<typename K, typename V>
bool HashTable<K, V>::add(const K& key, const V& value)
{
	cachedKey = key;
	if (!(arr + getAddress(key))->isEmpty())
		offTable++;
	//Calls hash function and stores at beginning of the list at computed index
	(arr + getAddress(key))->insertFirst(value);
	//Increments number of nodes
	count++;
	//If number of nodes are greater than table size
	if (calcLoadFactor() > (2.0/3.0))
		reHash(); //Rehashing
	return true;
}


template<typename K, typename V>
bool HashTable<K, V>::remove(const K& key)
{
	//Get hash address
	int index = getAddress(key);
	//Finds specific item's location in the list
	int position = (arr + index)->getPos(key);
	if (position == -1)
		return false;
	//Removes it from list
	(arr + index)->remove(position);
	if ((arr + index)->getCount() >= 1)
		offTable--;
	//Decrement Count
	count--;
	return true;
}

template<typename K, typename V>
bool HashTable<K, V>::remove(const K& key, const V& value)
{
	cachedKey = key;
	//Get hash address
	int index = getAddress(key);
	//Finds specific item's location in the list
	int position = (arr + index)->getPos(value);
	if (position == -1)
		return false;
	//Removes it from list
	(arr + index)->remove(position);
	if ((arr + index)->getCount() >= 1)
		offTable--;
	//Decrement Count
	count--;
	return true;
}

template<typename K, typename V>
int HashTable<K, V>::getAddress(const K& key)
{
	//Passes item to a genAlg function when data type of item is determined and returns a hash address
	return genAlg(key);
}


template<typename K, typename V>
int HashTable<K, V>::genAlg(int key) const
{
	//Return hash address
	return(static_cast<int>(key) % size);
}

template<typename K, typename V>
int HashTable<K, V>::genAlg(double key) const
{
	//Return hash address
	return(static_cast<int>(key) % size);
}

template<typename K, typename V>
int HashTable<K, V>::genAlg(char key) const
{
	//Return hash address
	return(static_cast<int>(key) % size);
}


template<typename K, typename V>
int HashTable<K, V>::genAlg(std::string key) const
{
	//Performs folding for string items
	int holder = 0;
	for (int i = 0; i < key.size(); i++)
	{
		//Folding each character
		holder += (int)key[i];
	}
	//Return hash address
	return (holder % size);
}

template<typename K, typename V>
int HashTable<K, V>::getOffTable() const
{
	//Return nodes off the table
	return offTable;
}

template<typename K, typename V>
void HashTable<K, V>::reHash()
{
	//Temporary array with count > size of table
	const int prevCount = count;
	//Pointer to an array to hold data values of array that needs resizing
	V* dataHolder = new V[prevCount];
	//Pointer to an array to hold key values of array that needs resizing
	K* keyHolder = new K[prevCount];
	//Iterates from 0 to count
	int j = 0;
	//Iterates through all linked lists in the table
	for (int i = 0; i < size; i++)
	{
		while (!(arr + i)->isEmpty())
		{
			V data;
			//Storing data and keys into their respective arrays
			data = (arr + i)->getFirstData();
			cachedKey = (arr + i)->getFirstKey();
			dataHolder[j] = data;
			keyHolder[j] = cachedKey;
			j++;
			//Removing processed node from the linked list
			(arr + i)->removeFirst();
			if (!(arr + i)->isEmpty())
				j++;
		}
	}
	//Multiplying size by 2
	size *= 2;
	//Getting the next available prime number
	size = getNextPrime();
	//Resetting count to 0
	count = 0;
	offTable = 0;
	//deleting array
	delete[] arr;
	//Redeclaring arr as a new pointer to an array of linked lists with updated size
	arr = new List<V>[size];
	//Reinserting all nodes back into the updated array
	for (int i = 0; i < prevCount; i++)
	{
		V data;
		data = dataHolder[i];
		cachedKey = keyHolder[i];
		add(cachedKey, data);
	}
	//deleting the holder arrays
	delete[] dataHolder;
	delete[] keyHolder;
}

template<typename K, typename V>
bool HashTable<K, V>::isEmpty()
{
	//Returns number of nodes present in the table
	return (count == 0);
}

template<typename K, typename V>
void HashTable<K, V>::empty()
{
	//Count set to zero
	count = 0;
	//Remove all elements of linked list across all indexes
	for (int i = 0; i < size; i++)
	{
		if (!(arr + i)->isEmpty())
			(arr + i)->removeAll();
	}

}

template<typename K, typename V>
HashTable<K, V>::~HashTable()
{
	//Empty all linked lists of nodes
	empty();
	//Delete the array
	arr = 0;
	delete[] arr;
}

template<typename K, typename V>
std::ostream& operator<<(std::ostream& os, const HashTable<K, V>& table)
{
	//Printing the table
	for (int i = 0; i < table.size; i++)
	{
		os << "Index: " << i << " ";
		if (!(table.arr + i)->isEmpty())
			os << *(table.arr + i);
		else
			os << std::endl;
	}
	return os;
}

//Returning the next available prime number
template<typename K, typename V>
int HashTable<K, V>::getNextPrime()
{
	bool flag = true;
	int n = size + 1;
	while (flag)
	{
		for (int i = 2; i < n; i++)
		{
			if (n % i == 0)
			{
				flag = false;
			}
		}
		if (flag)
			n++;
	}
	return n;
}


#endif //Hash_h
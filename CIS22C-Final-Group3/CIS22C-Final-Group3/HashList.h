/*********************************************************************************
 ********************************** HashList *************************************
 *********************************************************************************
 * Author: Hiren Rathod - 90% - Primary author
 * Author: Olivier Chan - 10% - Conversion to store references, use key/values
 *
 * The purpose of this class is to provide a List like ADT that works optimally for a hash table.
 * This HashList class inherits from the List ADT and allows for two separate types of template parameters.
 * This ADT links Hash Nodes, that also allow for separate template parameters, to create a list of hash nodes.
 * Within the hash table, the user is given the opportunity to enter key and value pairs.
 * The hash nodes store these pairs and link them to other nodes to provide full List ADT functionalities.
 *****************
 ***** USAGE *****
 *****************
 * Declare an object of this Hash List class with dual template initialization.
 * Perform Derived List operations on an object of this class
 * ADT functionalities:
 * Insert
 * Remove
 * Search
 * Retrieve Data
 * isEmpty
 *********************************************************************************/

#pragma once

#include "List.h"
#include "HashNode.h"

template <typename U, typename V> class HashList;
template <typename U, typename V>
std::ostream& operator<<(std::ostream& os, HashList<U, V>& hashList)
{
	for (int i = 0; i < hashList.getCount(); i++)
	{
		os << hashList.getData(i) << std::endl;
	}

	return os;
}

template<typename K, typename T>
class HashList : protected List<T>
{
protected:
    //Pointer to a hash node
    HashNode<K, T>* head;
    /*
     * insert
     *
     * brief: Private Function that inserts a Hash Node anywhere in the linked list
     *
     * param: newData - value that will be stored in table, pos - insertion position, k - hash key
     *
     * returns: Pointer to the inserted Hash Node
     */
    virtual HashNode<K, T>* insert(K k, T& newData, const int pos);
public:
    /*
     * HashList
     *
     * brief: Default Constructor that initializes head
     */
    HashList();
    /*
     * ~HashTable
     *
     * brief: Destructor that empties the list and frees memory
     */
    virtual ~HashList();
	/*
	 * isEmpty
	 *
	 * brief: Function that returns if the HashList has any values
	 *
	 * returns: bool value representing if there are any values in the list
	 */
	bool isEmpty() const override;
	/*
	 * getCount
	 *
	 * brief: Function that returns the number of nodes present in the table.
	 *
	 * returns: count
	 */
	int getCount() const override;
    /*
     * insertFirst
     *
     * brief: Function that adds a key/value pair into a Node and inserts that Node into the front of the list.
     *
     * param: key - hash key, item - value that will be stored in the list
     *
     * returns: Pointer to the inserted Hash Node
     */
    HashNode<K, T>* insertFirst(K, T&);
    /*
     * remove
     *
     * brief: Function that removes a hash node at a specific position in the list
     *
     * param: pos - location in list
     */
    void remove(const int pos) override;
    /*
     * removeFirst
     *
     * brief: Function that removes a hash node from the beginning of the list
     */
    void removeFirst() override;
    /*
     * remove
     *
     * brief: Function that removes all hash nodes from the list
     *
     * param: pos - location in list
     */
    void removeAll() override;
    /*
     * getData
     *
     * brief: Function that returns data at the specified location in the list
     *
     * param: pos - list position
     *
     * returns: Hash Node data
     */
    T& getData(const int pos) override;
    /*
     * getFirstData
     *
     * brief: Function that returns data at the beginning of the list
     *
     * returns: First Hash Node's data
     */
    T& getFirstData() override;
    /*
     * getFirstKey
     *
     * brief: Function that returns the first key at the beginning of the list
     *
     * returns: First Hash Node's key
     */
    K getFirstKey();
    /*
     * getPos
     *
     * brief: Function that returns the index of an item in the List
     *
     * param: item - value assumed to be in the list
     *
     * returns: index of where the node that containns the passe value is located
     */
    int getPos(const T& item);
    /*
     * getKey
     *
     * brief: Function that returns the key of a Hash Node at the specified location within the list
     *
     * returns: Traversed Hash Node's key
     */
    K getKey(const int pos);
};

template<typename K, typename T>
HashList<K, T>::HashList() : head(nullptr)
{

}

template<typename K, typename T>
HashList<K, T>::~HashList()
{
    HashList::removeAll();
}

template <typename K, typename T>
bool HashList<K, T>::isEmpty() const
{
	return List<T>::count == 0;
}

template <typename K, typename T>
int HashList<K, T>::getCount() const
{
	return List<T>::getCount();
}

template <typename K, typename T>
HashNode<K, T>* HashList<K, T>::insert(K k, T& newData, const int pos)
{
	if (pos < 0 || pos > List<T>::count)
	{
		throw std::out_of_range("Index out of range.");
	}

	HashNode<K, T>* returnNode;
	
    if (head == nullptr) //The list is empty
    {
        head = new HashNode<K, T>(k, newData);
		Efficiency::globalListOperations++;

		returnNode = head;
    }
	else if (pos == 0) //Replacing head
	{
		HashNode<K, T>* temp = head;
		head = new HashNode<K, T>(k, newData, temp);
		Efficiency::globalListOperations++;

		returnNode = head;
	}
    else
    {
        HashNode<K, T>* currentNode = head;
        for (int i = 0; i < pos - 1; i++)
        {
            currentNode = currentNode->next;
			Efficiency::globalListOperations++;
        }

        HashNode<K, T>* temp = currentNode->next;
        currentNode->next = new HashNode<K, T>(k, newData, temp);
		Efficiency::globalListOperations++;

		returnNode = currentNode->next;
    }

	List<T>::count++;
    return returnNode;
}

template<typename K, typename T>
HashNode<K, T>* HashList<K, T>::insertFirst(K k, T& newData)
{
    return insert(k, newData, 0);
}

template <typename K, typename T>
void HashList<K, T>::remove(const int pos)
{
	if (head == nullptr) //The list is empty
	{
		throw std::out_of_range("HashList is empty.");
	}

	if (pos < 0 || pos > List<T>::count - 1)
	{
		throw std::out_of_range("Index out of range.");
	}

    if (pos == 0)
    {
        HashNode<K, T>* nextNode = head->next;
        
        delete head;
        head = nextNode;
		Efficiency::globalListOperations++;
    }
    else
    {
        HashNode<K, T>* previousNode = nullptr;
        HashNode<K, T>* currentNode = head;
        for (int i = 0; i < pos; i++)
        {
            previousNode = currentNode;
            currentNode = currentNode->next;
			Efficiency::globalListOperations++;
        }

        previousNode->next = currentNode->next;
        
        delete currentNode;
		Efficiency::globalListOperations++;
    }

	List<T>::count--;
}

template <typename K, typename T>
void HashList<K, T>::removeFirst()
{
    remove(0);
}

template <typename K, typename T>
void HashList<K, T>::removeAll()
{
	if (head == nullptr) //The list is empty
	{
		return;
	}
    else
    {
        HashNode<K, T>* currentNode = head;
        while (currentNode->next != nullptr)
        {
            HashNode<K, T>* previousNode = currentNode;
            currentNode = currentNode->next;
            delete previousNode;
			Efficiency::globalListOperations++;
        }
        
        delete currentNode;
		Efficiency::globalListOperations++;
    }
	List<T>::count = 0;
    head = nullptr;
}

template <typename K, typename T>
T& HashList<K, T>::getData(const int pos)
{
	if (head == nullptr) //The list is empty
	{
		throw std::out_of_range("List is empty.");
	}

	if (pos < 0 || pos > List<T>::count - 1)
	{
		throw std::out_of_range("Index out of range.");
	}

	HashNode<K, T>* currentNode = head;
	for (int i = 0; i < pos; i++)
	{
		currentNode = currentNode->next;
		Efficiency::globalListOperations++;
	}

	Efficiency::globalListOperations++;
	return currentNode->data;
}

template <typename K, typename T>
K HashList<K, T>::getKey(const int pos)
{
    if (head == nullptr) //The list is empty
    {
        throw std::out_of_range("List is empty.");
    }
    
    if (pos < 0 || pos > (List<T>::count - 1))
    {
        throw std::out_of_range("Index out of range.");
    }
    
    HashNode<K, T>* currentNode = head;
    
    for (int i = 0; i < pos; i++)
    {
        currentNode = currentNode->next;
		Efficiency::globalListOperations++;
    }
    return currentNode->key;
}

template <typename K, typename T>
T& HashList<K, T>::getFirstData()
{
    return getData(0);
}

template <typename K, typename T>
K HashList<K, T>::getFirstKey()
{
    return getKey(0);
}

template<typename K, typename T>
int HashList<K, T>::getPos(const T& item)
{
	int pos = 0;
	HashNode<K, T> *current = head;
	while (current != nullptr)
	{
		Efficiency::globalListOperations++;
		if (current->data == item)
			return pos;
		pos++;
		current = current->next;
	}
	return -1;
}
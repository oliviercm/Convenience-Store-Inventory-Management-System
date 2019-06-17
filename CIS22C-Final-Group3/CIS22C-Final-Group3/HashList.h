#pragma once
/********************************************************************************
 ************************************ HashList ***************************************
 *********************************************************************************
 * Author: Hiren Rathod - 100%
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


#include "List.h"
#include "HashNode.h"
#include <iostream>

template<typename K, typename T>
class HashList : protected List<T>
{
private:
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
    virtual HashNode<K, T>* insert(const T& newData, const int pos, const K& k);
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
    bool isEmpty() const;
    /*
     * getCount
     *
     * brief: Function that returns the number of nodes present in the table.
     *
     * returns: count
     */
    int getCount() const;
    /*
     * insertFirst
     *
     * brief: Function that adds a key/value pair into a Node and inserts that Node into the front of the list.
     *
     * param: key - hash key, item - value that will be stored in the list
     *
     * returns: Pointer to the inserted Hash Node
     */
    HashNode<K, T>* insertFirst(const K&, const T&);
    /*
     * remove
     *
     * brief: Function that removes a hash node at a specific position in the list
     *
     * param: pos - location in list
     */
    void remove(const int pos);
    /*
     * removeFirst
     *
     * brief: Function that removes a hash node from the beginning of the list
     */
    void removeFirst();
    /*
     * remove
     *
     * brief: Function that removes all hash nodes from the list
     *
     * param: pos - location in list
     */
    void removeAll();
    /*
     * getData
     *
     * brief: Function that returns data at the specified location in the list
     *
     * param: pos - list position
     *
     * returns: Hash Node data
     */
    T& getData(const int pos);
    /*
     * getFirstData
     *
     * brief: Function that returns data at the beginning of the list
     *
     * returns: First Hash Node's data
     */
    T& getFirstData();
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
    int getPos(T item);
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
HashList<K, T>::HashList()
{
    //Initializing head
    head = 0;
}

template<typename K, typename T>
HashList<K, T>::~HashList()
{
    //Emptying the lists
    List<T>::~List();
    removeAll();
    delete head;
}

template <typename K, typename T>
bool HashList<K, T>::isEmpty() const
{
    return List<T>::isEmpty();
}

template <typename K, typename T>
int HashList<K, T>::getCount() const
{
    return List<T>::getCount();
}

template <typename K, typename T>
HashNode<K, T>* HashList<K, T>::insert(const T& data, const int pos, const K& k)
{
    Node<T>* holder = List<T>::insert(data, pos);
    HashNode<K, T> *newHnode = new HashNode<K,T>(data);
    newHnode->data = holder->data;
    newHnode->key = k;
    if (head == nullptr || pos == 0) //The list is empty
    {
        head = newHnode;
        head->HashNode<K,T>::next = 0;
    }
    else
    {
        HashNode<K, T>* currentNode = head;
        for (int i = 0; i < pos - 1; i++)
        {
            currentNode = currentNode->HashNode<K,T>::next;
        }
        HashNode<K, T>* temp = currentNode->next;
        currentNode->next = newHnode;
    }
    return newHnode;
}

template<typename K, typename T>
HashNode<K, T>* HashList<K, T>::insertFirst(const K& k, const T& newData)
{
    return insert(newData, 0, k);
}

template <typename K, typename T>
void HashList<K, T>::remove(const int pos)
{
    if (List<T>::count == 0)
        return;
    if (pos == 0)
    {
        
        HashNode<K, T>* nextNode = head->next;
        
        delete head;
        head = nextNode;
    }
    else
    {
        HashNode<K, T>* previousNode = nullptr;
        HashNode<K, T>* currentNode = head;
        for (int i = 0; i < pos; i++)
        {
            previousNode = currentNode;
            currentNode = currentNode->next;
        }
        
        if (currentNode->next != nullptr)
        {
            HashNode<K, T>* temp = currentNode->next;
            previousNode->next = temp;
        }
        
        delete currentNode;
    }
}

template <typename K, typename T>
void HashList<K, T>::removeFirst()
{
    List<T>::remove(0);
    remove(0);
    return;
}

template <typename K, typename T>
void HashList<K, T>::removeAll()
{
    List<T>::removeAll();
    if (head == nullptr) //The list is empty
        return;
    else
    {
        HashNode<K, T>* currentNode = head;
        while (currentNode->next != nullptr)
        {
            HashNode<K, T>* previousNode = currentNode;
            currentNode = currentNode->next;
            delete previousNode;
        }
        
        delete currentNode;
    }
    head = nullptr;
    return;
}

template <typename K, typename T>
T& HashList<K, T>::getData(const int pos)
{
    return List<T>::getData(pos);
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
int HashList<K, T>::getPos(T item)
{
    return List<T>::getPos(item);
}

template <typename U, typename V>
std::ostream& operator<<(std::ostream& os, HashList<U, V> & list)
{
    os << (List<V> &) list;
    return os;
}


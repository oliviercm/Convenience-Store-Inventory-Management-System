/********************************************************************************
 ********************************* HashNode *************************************
 ********************************************************************************
 * Author: Hiren Rathod - 95% - Primary author
 * Author: Olivier Chan - 5% - Conversion to store references, use key/values
 *
 * The purpose of this struct is to extend from the typical Node Struct while introducing a key variable.
 * This HashNode struct inherits from Node Struct and allows for two separate types of template parameters.
 * Within the hash table, the user is given the opportunity to enter key and value pairs.
 * The hash nodes store these pairs.
 *****************
 ***** USAGE *****
 *****************
 * Instantiate this struct and set the variables
 * Manipulate the data and allow for use in the List ADTs
 ********************************************************************************/

#pragma once

#include "Node.h"

template <typename K, typename T>
struct HashNode : Node<T>
{
    //Key
    K key;
    //Next pointer
    HashNode<K, T>* next;
    //Constructors
    HashNode(K, T&);
    HashNode(K, T&, HashNode<K, T>*);
};

template <typename K, typename T>
HashNode<K, T>::HashNode(K k, T& d) : Node<T>(d), key(k), next(nullptr)
{
    
}

template <typename K, typename T>
HashNode<K, T>::HashNode(K k, T& d, HashNode<K, T>* n) : Node<T>(d), key(k), next(n)
{
    
}

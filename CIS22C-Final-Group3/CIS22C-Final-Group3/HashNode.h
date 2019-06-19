#pragma once
/********************************************************************************
 ************************************ HashList ***************************************
 *********************************************************************************
 * Author: Hiren Rathod - 100%
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
 *********************************************************************************/
#include "Node.h"
template <typename K, typename T>
struct HashNode : Node<T>
{
    //Key
    K key;
    //Next pointer
    HashNode<K, T>* next = nullptr;
    //Constructors
    HashNode(T&);
    HashNode();
};

template <typename K, typename T>
HashNode<K,T>::HashNode(T& dt) : Node<T>(dt)
{
    
}

template <typename K, typename T>
HashNode<K, T>::HashNode()
{
    next = nullptr;
}


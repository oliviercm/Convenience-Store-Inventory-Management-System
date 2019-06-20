/********************************************************************************
********************************** BST_Node *************************************
*********************************************************************************
* Author: Olivier Chan - 50%
* Author: Luis Guerrero - 50%
*
* This class is part of a BST (binary search tree) abstract data structure.
* The purpose of this class is to act as a data-containing node in a tree structure,
* with each node having a branch to two deeper nodes.
*****************
***** USAGE *****
*****************
* This class should only be used within the BST class.
* Creating a BST_Node must be done with a reference to the contained data.
* The left and right nodes may be given as parameters or set using functions.
*********************************************************************************/

#pragma once

template <typename K, typename V>
struct BST_Node
{
public:
	K key;
	V& value;
	BST_Node<K, V>* left;
	BST_Node<K, V>* right;

	BST_Node(K, V&, BST_Node<K, V>* = nullptr, BST_Node<K, V>* = nullptr);
	virtual ~BST_Node() = default;
};

template <typename K, typename V>
BST_Node<K, V>::BST_Node(K k, V& v, BST_Node<K, V>* l, BST_Node<K, V>* r) : key(k), value(v), left(l), right(r)
{

}
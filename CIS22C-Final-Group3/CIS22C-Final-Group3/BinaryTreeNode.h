/********************************************************************************
********************************** BST Node *************************************
*********************************************************************************
* Author: Yue Pan - 95% - Primary author
* Author: Olivier Chan - 5% - Conversion to store references
*
* The purpose of this class is act as the data container for a BST ADT.
*****************
***** USAGE *****
*****************
* Declare nodes with BinaryTreeNode(referenceToData)
*********************************************************************************/

#pragma once
#ifndef BINARYTREENODE
#define BINARYTREENODE

template <typename T>
struct BinaryTreeNode
{
public:
	T& datum;
	BinaryTreeNode<T> * left_ptr;
	BinaryTreeNode<T> * right_ptr;

	BinaryTreeNode(T &);
	virtual ~BinaryTreeNode() = default;
};

template <typename T>
BinaryTreeNode<T>::BinaryTreeNode(T & d) : datum(d), left_ptr(nullptr), right_ptr(nullptr)
{

}

#endif
#pragma once
#ifndef BINARYTREENODE
#define BINARYTREENODE

template <typename T>
class BinaryTreeNode
{
public:
	T datum;
	BinaryTreeNode<T> * left_ptr;
	BinaryTreeNode<T> * right_ptr;
	BinaryTreeNode(const T &);
	BinaryTreeNode();
	~BinaryTreeNode();
};

template <typename T>
BinaryTreeNode<T>::BinaryTreeNode()
{
	left_ptr = nullptr;
	right_ptr = nullptr;
}

template <typename T>
BinaryTreeNode<T>::BinaryTreeNode(const T & i_item)
{
	datum = i_item;
	left_ptr = nullptr;
	right_ptr = nullptr;
}

template <typename T>
BinaryTreeNode<T>::~BinaryTreeNode()
{
	datum = NULL;
	left_ptr = nullptr;
	right_ptr = nullptr;
}

#endif
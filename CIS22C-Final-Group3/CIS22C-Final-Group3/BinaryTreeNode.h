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
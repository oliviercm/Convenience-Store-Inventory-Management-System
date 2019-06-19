/********************************************************************************
************************************ Node ***************************************
*********************************************************************************
* Author: Olivier Chan - 70%
* Author: Luis Guerrero - 30%
*
* The purpose of this class is to provide data container for List.
*****************
***** USAGE *****
*****************
* This class is a structure used for linked list nodes.
* 
* Nodes must be initialized with a valid reference.
*********************************************************************************/

#pragma once

template <typename T>
struct Node
{
public:
	T& data;
	Node<T>* next;

	Node(T&);
	Node(T&, Node<T>*);
	virtual ~Node() = default;
};

template <typename T>
Node<T>::Node(T& d) : data(d), next(nullptr)
{

}
template <typename T>
Node<T>::Node(T& d, Node<T>* n) : data(d), next(n)
{

}

#pragma once
/********************************************************************************
************************************ Node ***************************************
*********************************************************************************
* Author: Olivier Chan - 70%
* Author: Luis Guerrero - 30%
*
* The purpose of this class is to provide a Node ADT.
*****************
***** USAGE *****
*****************
* WIP
*********************************************************************************/

#pragma once
#include <iostream>

template <typename T>
struct Node
{
public:
	T data;
	T key;
	Node<T>* next;

	Node(const T&);
	Node(const T&, Node<T>*);
	Node(T&&);
	Node(T&&, Node<T>*);
};

template <typename T>
Node<T>::Node(const T& d) : data(d), next(nullptr)
{

}

template <typename T>
Node<T>::Node(T&& d) : data(d), next(nullptr)
{

}

template <typename T>
Node<T>::Node(const T& d, Node<T>* n) : data(d), next(n)
{

}

template <typename T>
Node<T>::Node(T&& d, Node<T>* n) : data(d), next(n)
{

}
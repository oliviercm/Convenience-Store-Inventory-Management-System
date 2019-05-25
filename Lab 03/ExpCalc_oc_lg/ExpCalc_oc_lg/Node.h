#pragma once

template <typename T>
struct Node
{
public:
	T& data;
	Node<T>* next;

	Node(T&);
	Node(T&, Node<T>*);
};

template <typename T>
Node<T>::Node(T& d) : data(d)
{
	next = nullptr;
}

template <typename T>
Node<T>::Node(T& d, Node<T>* n) : data(d), next(n)
{

}
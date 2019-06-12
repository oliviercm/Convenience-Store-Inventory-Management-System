#pragma once
#ifndef STACK1_H
#define STACK1_H

#include <iostream>
#include "OrderedList.h"
#include "Node.h"

template <typename T>
class Stack1 : protected OrderedList<T>
{
public:
	class StackEmpty
	{};

	Stack1();

	~Stack1();

	void push(T);
	T pop();
	T peek();
	bool isEmpty_stack();
	void clear_stack();
	int size_stack();

	template <typename T> friend std::ostream & operator<<(std::ostream &, const Stack1<T> &);
};

template <typename T>
Stack1<T>::Stack1() : OrderedList<T>()
{}

template <typename T>
Stack1<T>::~Stack1()
{
	clear_stack();
}

/*
functionality of this member function is that it will add  the new node with the input node value at the top of one stack
pre: T type node value
post: it will add  the new node with the input node value at the top of this stack with no returning
*/
template <typename T>
void Stack1<T>::push(T item)
{
	Node<T> * new_ptr = new Node<T>;
	new_ptr->value = item;
	if (OrderedList<T>::header_ptr->head->next == nullptr)
	{
		new_ptr->next = nullptr;
		OrderedList<T>::header_ptr->head->next = new_ptr;
		new_ptr = nullptr;
	}
	else
	{
		new_ptr->next = OrderedList<T>::header_ptr->head->next;
		OrderedList<T>::header_ptr->head->next = new_ptr;
		new_ptr = nullptr;
	}
	OrderedList<T>::header_ptr->count += 1;
}

/*
functionality of this member function is that it will pop out the node at the top of one stack
pre: T type node value
post: it will pop out the node at the top of one stack with returning the node
*/
template <typename T>
T Stack1<T>::pop()
{
	T return_value;
	if (OrderedList<T>::header_ptr->head->next == nullptr)
	{
		throw StackEmpty();
	}
	else if (OrderedList<T>::header_ptr->head->next->next == nullptr)
	{
		Node<T> * ptr1 = OrderedList<T>::header_ptr->head->next;
		OrderedList<T>::header_ptr->head->next = nullptr;
		return_value = ptr1->value;
		delete ptr1;
		ptr1 = nullptr;
	}
	else
	{
		Node<T> * ptr1 = OrderedList<T>::header_ptr->head;
		Node<T> * ptr2 = OrderedList<T>::header_ptr->head->next;
		ptr1->next = ptr2->next;
		return_value = ptr2->value;
		delete ptr2;
		ptr1 = nullptr;
		ptr2 = nullptr;
	}
	OrderedList<T>::header_ptr->count -= 1;
	return return_value;
}

/*
functionality of this member function is that it will show the node at the top of one stack
pre: T type node value
post: it will show the node at the top of one stack with returning the top node
*/
template <typename T>
T Stack1<T>::peek()
{
	if (OrderedList<T>::header_ptr->head->next == nullptr)
	{
		throw StackEmpty();
	}
	else
	{
		return OrderedList<T>::header_ptr->head->next->value;
	}
}

/*
functionality of this member function is that it will try to find out that if this stack is empty
pre: no input
post: it will try to find out that if this stack is empty with returning true if it does otherwise returning false
*/
template <typename T>
bool Stack1<T>::isEmpty_stack()
{
	return OrderedList<T>::isEmpty();
}

/*
functionality of this member function is that it will eliminate all nodes in one stack
pre: no input
post: it will eliminate all nodes in this stack with no returning value
*/
template <typename T>
void Stack1<T>::clear_stack()
{
	if (OrderedList<T>::header_ptr->head->next == nullptr)
	{
	}
	else
	{
		Node<T> * ptr1;
		Node<T> * ptr2;
		while (OrderedList<T>::header_ptr->head->next->next != nullptr)
		{
			ptr1 = OrderedList<T>::header_ptr->head;
			ptr2 = OrderedList<T>::header_ptr->head->next;
			ptr1->next = ptr2->next;
			delete ptr2;
		}
		ptr1 = OrderedList<T>::header_ptr->head->next;
		OrderedList<T>::header_ptr->head->next = nullptr;
		delete ptr1;
		ptr1 = nullptr;
		ptr2 = nullptr;
		OrderedList<T>::header_ptr->count = 0;
	}
}

/*
functionality of this member function is that it will calculate how many nodes are in this stack
pre: no input
post: it will calculate how many nodes are in one stack and return this total number
*/
template <typename T>
int Stack1<T>::size_stack()
{
	return OrderedList<T>::size();
}

/*
functionality of this member function is overloading the ofstream
pre: ofstream and const OrderedList<T>
post: it will overload the ofstream to properly output one stack object
*/
template <typename T>
std::ostream & operator<<(std::ostream & strm, const Stack1<T> & right)
{
	Node<T> * ptr1 = right.header_ptr->head->next;
	if (ptr1 == nullptr)
	{
		strm << "top ->  <- base";
		return strm;
	}
	strm << "top -> ";
	while (ptr1->next != nullptr)
	{
		strm << ptr1->value << " ";
		ptr1 = ptr1->next;
	}
	strm << ptr1->value << " ";
	strm << "<- base";
	return strm;
}

#endif

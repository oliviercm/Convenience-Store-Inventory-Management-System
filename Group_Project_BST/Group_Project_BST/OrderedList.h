#pragma once
#ifndef ORDEREDLIST_H
#define ORDEREDLIST_H

#include <iostream>
#include "Node.h"

template <typename T>
class OrderedList
{
protected:
	struct Header
	{
		int count;
		Node<T> *  head;
		Node<T> *  end;
	};
	Header * header_ptr;
	void insert_at(T, int);
public:
	class out_of_range
	{};
	class empty_ordered_linked_list
	{};

	OrderedList();

	virtual ~OrderedList();

	void add(T);
	void remove(T);
	void remove_at(int);
	bool search(T);
	T search_at(int);
	bool isEmpty();
	void clear();
	int size();
	void reverse();
	void merge(const OrderedList<T> &);

	//pay attention to "Linker Tools Error LNK2019"
	template<typename T> friend std::ostream & operator<<(std::ostream & strm, const OrderedList<T> &);
};

template <typename T>
OrderedList<T>::OrderedList()
{
	header_ptr = new Header;
	header_ptr->count = 0;
	Node<T> * new_ptr = new Node<T>;
	new_ptr->next = nullptr;
	header_ptr->head = new_ptr;
	header_ptr->end = new_ptr;
	new_ptr = nullptr;
}

template <typename T>
OrderedList<T>::~OrderedList()
{
	clear();
	delete header_ptr->head;
	delete header_ptr;
}

template <typename T>
void OrderedList<T>::insert_at(T item, int index)
{
	if (index < 1 || index > header_ptr->count + 1)
	{
		throw  out_of_range();
	}
	Node<T> * new_ptr = new Node<T>;
	new_ptr->value = item;
	new_ptr->next = nullptr;
	Node<T> * ptr1 = header_ptr->head;
	Node<T> * ptr2 = header_ptr->head->next;
	while (index > 1)
	{
		ptr1 = ptr2;
		ptr2 = ptr2->next;
		index -= 1;
	}
	ptr1->next = new_ptr;
	new_ptr->next = ptr2;
	new_ptr = nullptr;
	ptr1 = nullptr;
	ptr2 = nullptr;
}

/*
functionality of this member function is that it will add  the new node with the input node value to its correct position
pre: T type node value
post: it will add  the new node with the input node value to its correct position with no returning
*/
template <typename T>
void OrderedList<T>::add(T item)
{
	header_ptr->count += 1;
	if (header_ptr->head->next == nullptr)
	{
		Node<T> * new_ptr = new Node<T>;
		new_ptr->value = item;
		new_ptr->next = nullptr;
		header_ptr->head->next = new_ptr;
		new_ptr = nullptr;
	}
	else
	{
		Node<T> * new_ptr = new Node<T>;
		new_ptr->value = item;
		new_ptr->next = nullptr;
		Node<T> * ptr1 = header_ptr->head;
		Node<T> * ptr2 = ptr1->next;
		while (ptr2->next != nullptr)
		{
			if (ptr2->value > item)
			{
				new_ptr->next = ptr2;
				ptr1->next = new_ptr;
				new_ptr = nullptr;
				return;
			}
			else
			{
				ptr1 = ptr2;
				ptr2 = ptr2->next;
			}
		}
		if (ptr2->value > item)
		{
			new_ptr->next = ptr2;
			ptr1->next = new_ptr;
			new_ptr = nullptr;
		}
		else
		{
			ptr2->next = new_ptr;
			new_ptr = nullptr;
		}
	}
}

/*
functionality of this member function is that it will remove  the node with the input node value from the linked list
pre: T type node value
post: it will remove  the node with the input node value from the linked list with no returning
*/
template <typename T>
void OrderedList<T>::remove(T item)
{
	Node<T> * ptr1 = header_ptr->head;
	if (ptr1->next == nullptr)
	{
		ptr1 = nullptr;
		return;
	}
	else
	{
		Node<T> * ptr2 = ptr1->next;
		while (ptr2->value <= item && ptr2->next != nullptr)
		{
			if (ptr2->value == item)
			{
				ptr1->next = ptr2->next;
				ptr2->next = nullptr;
				delete ptr2;
				ptr2 = ptr1->next;
				header_ptr->count -= 1;
			}
			else if (ptr2->value < item)
			{
				ptr1 = ptr2;
				ptr2 = ptr2->next;
			}
		}
		if (ptr2->value == item)
		{
			ptr1->next = nullptr;
			delete ptr2;
			header_ptr->count -= 1;
		}
		ptr1 = nullptr;
		ptr2 = nullptr;
	}
}

/*
functionality of this member function is that it will remove  the node at certain index from the linked list
pre: int type index
post: it will remove the node at certain index from the linked list with no returning
*/
template <typename T>
void OrderedList<T>::remove_at(int index)
{
	if (header_ptr->count == 0)
	{
		throw empty_ordered_linked_list();
	}
	else
	{
		if (index < 1 || index > header_ptr->count)
		{
			throw out_of_range();
		}
		else
		{
			Node<T> * ptr1 = header_ptr->head;
			Node<T> * ptr2 = header_ptr->head->next;
			for (int ind = 1; ind != index; ind++)
			{
				ptr1 = ptr2;
				ptr2 = ptr2->next;
			}
			if (index == header_ptr->count)
			{
				ptr1->next = nullptr;
				delete ptr2;
				header_ptr->count -= 1;
				ptr1 = nullptr;
				ptr2 = nullptr;
			}
			else
			{
				ptr1->next = ptr2->next;
				delete ptr2;
				header_ptr->count -= 1;
				ptr1 = nullptr;
				ptr2 = nullptr;
			}
		}
	}
}

/*
functionality of this member function is that it will try to find out if the node value exists in the linked list
pre: T type node value
post: it will try to find out if the node value exists in the linked list with returning true if it does otherwise returning false
*/
template <typename T>
bool OrderedList<T>::search(T item)
{
	Node<T> * ptr1 = header_ptr->head->next;
	while (ptr1->value <= item && ptr1->next != nullptr)
	{
		if (ptr1->value < item)
		{
			ptr1 = ptr1->next;
		}
		else if (ptr1->value == item)
		{
			return true;
		}
	}
	if (ptr1->value == item && ptr1->next == nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
functionality of this member function is that it will try to find out the node value at certain index of one linked list
pre: int type index
post: it will try to find out the node value at certain index of one linked list
*/
template <typename T>
T OrderedList<T>::search_at(int index)
{
	if (header_ptr->count == 0)
	{
		throw empty_ordered_linked_list();
	}
	else
	{
		if (index < 1 || index > header_ptr->count)
		{
			throw out_of_range();
		}
		else
		{
			Node<T> * ptr1 = header_ptr->head;
			Node<T> * ptr2 = header_ptr->head->next;
			for (int count = 1; count < index; count++)
			{
				ptr1 = ptr2;
				ptr2 = ptr2->next;
			}
			return ptr2->value;
		}
	}
}

/*
functionality of this member function is that it will try to find out that if this linked list is empty
pre: no input
post: it will try to find out that if this linked list is empty with returning true if it does otherwise returning false
*/
template <typename T>
bool OrderedList<T>::isEmpty()
{
	if (header_ptr->count == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
functionality of this member function is that it will eliminate all nodes in this linked list
pre: no input
post: it will eliminate all nodes in this linked list with no returning value
*/
template <typename T>
void OrderedList<T>::clear()
{
	Node<T> * ptr1;
	Node<T> * ptr2;
	if (header_ptr->head->next == nullptr)
	{
	}
	else
	{
		ptr1 = header_ptr->head;
		ptr2 = header_ptr->head->next;
		while (ptr2->next != nullptr)
		{
			ptr1 = ptr2;
			ptr2 = ptr2->next;
			delete ptr1;
		}
		delete ptr2;
	}
	header_ptr->count = 0;
	header_ptr->head->next = nullptr;
}

/*
functionality of this member function is that it will calculate how many nodes are in this linked list
pre: no input
post: it will calculate how many nodes are in this linked list and return this total number
*/
template <typename T>
int OrderedList<T>::size()
{
	return header_ptr->count;
}

template <typename T>
void OrderedList<T>::reverse()
{
	if (header_ptr->count <= 1)
	{
	}
	else
	{
		T temp;
		int counter = header_ptr->count;
		while (counter > 1)
		{
			temp = (*this).search_at(1);
			(*this).remove_at(1);
			(*this).insert_at(temp, counter);
			counter -= 1;
		}
	}
}

template <typename T>
void OrderedList<T>::merge(const OrderedList<T> & right)
{
	if (right.header_ptr->count == 0)
	{
	}
	else
	{
		Node<T> * ptr1 = right.header_ptr->head->next;
		while (ptr1 != nullptr)
		{
			(*this).add(ptr1->value);
			ptr1 = ptr1->next;
		}
	}
}

/*
functionality of this member function is overloading the ofstream
pre: ofstream and const OrderedList<T>
post: it will overload the ofstream to properly output one linked list object
*/
template <typename T>
std::ostream & operator<<(std::ostream & strm, const OrderedList<T> & right)
{
	strm << "head -> ";
	Node<T> * ptr1 = right.header_ptr->head->next;
	if (ptr1 == nullptr)
	{
		return strm;
	}
	while (ptr1->next != nullptr)
	{
		strm << ptr1->value << " -> ";
		ptr1 = ptr1->next;
	}
	strm << ptr1->value;
	return strm;
}

#endif
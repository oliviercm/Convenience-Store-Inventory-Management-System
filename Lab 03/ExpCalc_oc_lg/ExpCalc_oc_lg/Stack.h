/********************************************************************************
************************************ Stack **************************************
*********************************************************************************
* This class is an Abstract Data Structure, modeling the functionality of a stack.
* As this class is template based, it can be used with almost any type of data.
* This data structure follows a First In, Last Out pattern.
*****************
***** USAGE *****
*****************
* Declare an object of type Stack, using template initialization.
* You may then call Stack functions on the new Queue object.
*********************************************************************************/

#pragma once

#include "List.h"

template <typename T>
class Stack : protected List<T>
{
public:
	void push(T&);
	T& pop();
	T& peek();
	void empty();
	int getCount();
	bool isEmpty();
};

/*
Puts data into stack.

@pre New data.

@post Insert the firts element.

@return N/A.
*/

template <typename T>
void Stack<T>::push(T& newData)
{
	this->insertFirst(newData);
}

/*
Removes data from the stack.

@pre None.

@post Removes the first stacked element.

@return N/A.
*/

template <typename T>
T& Stack<T>::pop()
{
	T& data = this->getFirstData();
	
	this->removeFirst();

	return data;
}

/*
Gets the first elemnt in the stack.

@pre None.

@post Gets the firts element.

@return First element in the stack.
*/
template <typename T>
T& Stack<T>::peek()
{
	return this->getFirstData();
}

/*
Empties out the stack.

@pre None.

@post Removes all the stack.

@return N/A.
*/

template <typename T>
void Stack<T>::empty()
{
	this->removeAll();
}

/**
* count
*
* @brief Returns the number of elements in the stack.
*
* @return The number of elements in the stack.
*/

template <typename T>
int Stack<T>::getCount()
{
	return this->count;
}


/**
* isEmpty
*
* @brief Returns whether the stack is empty or not.
*
* @return TRUE if the stack is empty, otherwise FALSE
*/

template <typename T>
bool Stack<T>::isEmpty()
{
	if (this->getCount() == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
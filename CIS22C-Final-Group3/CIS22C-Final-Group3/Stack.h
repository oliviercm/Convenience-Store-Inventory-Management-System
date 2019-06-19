/********************************************************************************
************************************ Stack **************************************
*********************************************************************************
* Author: Olivier Chan - 50%
* Author: Luis Guerrero - 50%
*
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
	Stack() = default;
	virtual ~Stack() = default;

	Stack(const Stack&) = delete;
	Stack& operator=(const Stack&) = delete;
	
	void push(T&);
	T pop();
	T& peek();
	void empty();
	int getCount() const override;
	bool isEmpty() const override;
};

/*
Puts data into stack.

@pre New data.

@post Insert the first element.

@return N/A.
*/

template <typename T>
void Stack<T>::push(T& newData)
{
	List<T>::insertFirst(newData);
}

/*
Removes data from the stack.

@pre None.

@post Removes the first stacked element.

@return N/A.
*/

template <typename T>
T Stack<T>::pop()
{
	if (List<T>::isEmpty())
	{
		throw std::out_of_range("Stack is empty.");
	}
	
	T data = List<T>::getFirstData();
	
	List<T>::removeFirst();

	return std::move(data);
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
	if (List<T>::isEmpty())
	{
		throw std::out_of_range("Stack is empty.");
	}
	
	return List<T>::getFirstData();
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
	List<T>::removeAll();
}

/**
* count
*
* @brief Returns the number of elements in the stack.
*
* @return The number of elements in the stack.
*/

template <typename T>
int Stack<T>::getCount() const
{
	return List<T>::getCount();
}


/**
* isEmpty
*
* @brief Returns whether the stack is empty or not.
*
* @return TRUE if the stack is empty, otherwise FALSE
*/

template <typename T>
bool Stack<T>::isEmpty() const
{
	return List<T>::isEmpty();
}
/********************************************************************************
************************************ Queue **************************************
*********************************************************************************
* This class is an Abstract Data Structure, modeling the functionality of a queue.
* As this class is template based, it can be used with almost any type of data.
* This data structure follows a First In, First Out pattern.
* A real world analogy is the line of customers at a supermarket.
* Using Queue functions, you can:
*	- Add to the back of the queue
*	- Remove from the front of the queue
*	- View the front and back of the queue
*	- Get the count of elements in the queue
*	- Empty the queue
*	- Find out whether the queue is empty
*****************
***** USAGE *****
*****************
* Declare an object of type Queue, using template initialization.
* You may then call Queue functions on the new Queue object.
* Keep in mind:
*	- The Queue class is not designed to handle deletion of its elements, only
*		keep track of them.
*		Therefore, Queue does not delete its elements after Queue itself is deleted.
*********************************************************************************/

#pragma once

#include "List.h"

template<typename T>
class Queue : protected List<T>
{
protected:
	Node<T>* front; //The node in the front of the queue
	Node<T>* rear; //The node in the back of the queue
public:
	Queue();

	void enqueue(T&);
	T& dequeue();
	T& getFront();
	T& getRear();
	int getCount();
	void empty();
	bool isEmpty();
};

template<typename T>
Queue<T>::Queue()
{
	front = nullptr;
	rear = nullptr;
}

/**
* enqueue
*
* @brief Adds the passed data to the front of the queue.
*
* @param newData The data to add to the front of the queue.
*/
template<typename T>
void Queue<T>::enqueue(T& newData)
{
	Node<T>* temp = (this->insertLast(newData));
	if (this->front == nullptr)
	{
		this->front = temp;
		this->rear = temp;
	}
	else
	{
		this->rear = temp;
	}
}

/**
* dequeue
*
* @brief Removes the data at the end of the queue. Note that this doesn't actually delete the data itself.
*/

template<typename T>
T& Queue<T>::dequeue()
{
	if (this->isEmpty())
	{
		throw "Queue empty";
	}

	T& data = this->getFirstData();
	
	if (this->front == this->rear)
	{
		this->removeFirst();
		this->front = nullptr;
		this->rear = nullptr;
	}
	else
	{
		Node<T>* next = this->front->next;
		this->removeFirst();
		this->front = next;
	}

	return data;
}

/**
* getFront
*
* @brief Returns the data in the front of the queue.
*
* @return The data in the front of the queue.
*/

template<typename T>
T& Queue<T>::getFront()
{
	return this->getFirstData();
}

/**
* getRear
*
* @brief Returns the data in the rear of the queue.
*
* @return The data in the rear of the queue.
*/

template<typename T>
T& Queue<T>::getRear()
{
	return this->getLastData();
}

/**
* emptyQueue
*
* @brief Removes all elements from the queue.
*/

template<typename T>
void Queue<T>::empty()
{
	this->removeAll();
}

/**
* getCount
*
* @brief Returns the number of elements in the queue.
*
* @return The number of elements in the queue.
*/

template<typename T>
int Queue<T>::getCount()
{
	return this->count;
}

/**
* isEmpty
*
* @brief Returns whether the queue is empty or not.
*
* @return TRUE if the queue is empty, otherwise FALSE
*/

template<typename T>
bool Queue<T>::isEmpty()
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
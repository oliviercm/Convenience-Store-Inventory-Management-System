/********************************************************************************
************************************ Queue **************************************
*********************************************************************************
* Author: Olivier Chan - 50%
* Author: Luis Guerrero - 50%
* 
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
private:
	Node<T>* front; //The node in the front of the queue
	Node<T>* rear; //The node in the back of the queue
public:
	Queue();
	virtual ~Queue() = default;

	Queue(const Queue&) = delete;
	Queue& operator=(const Queue&) = delete;

	void enqueue(const T&);
	void enqueue(T&&);
	T dequeue();
	T& getFront();
	T& getRear();
	void empty();
	int getCount() const override;
	bool isEmpty() const override;
};

template<typename T>
Queue<T>::Queue() : front(nullptr), rear(nullptr)
{

}

/**
* enqueue
*
* @brief Adds the passed data to the front of the queue.
*
* @param newData The data to add to the front of the queue.
*/

template<typename T>
void Queue<T>::enqueue(const T& newData)
{
	Node<T>* temp = List<T>::insertLast(newData);
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
template<typename T>
void Queue<T>::enqueue(T&& newData)
{
	Node<T>* temp = List<T>::insertLast(newData);
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
* @brief Removes the data at the end of the queue.
*/

template<typename T>
T Queue<T>::dequeue()
{
	if (List<T>::isEmpty())
	{
		throw std::out_of_range("Queue is empty.");
	}

	T data = List<T>::getFirstData();
	
	if (this->front == this->rear)
	{
		List<T>::removeFirst();
		this->front = nullptr;
		this->rear = nullptr;
	}
	else
	{
		Node<T>* next = this->front->next;
		this->removeFirst();
		this->front = next;
	}

	return std::move(data);
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
	return this->front.data;
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
	return this->rear.data;
}

/**
* emptyQueue
*
* @brief Removes all elements from the queue.
*/

template<typename T>
void Queue<T>::empty()
{
	List<T>::removeAll();
}

/**
* getCount
*
* @brief Returns the number of elements in the queue.
*
* @return The number of elements in the queue.
*/

template<typename T>
int Queue<T>::getCount() const
{
	return List<T>::count;
}

/**
* isEmpty
*
* @brief Returns whether the queue is empty or not.
*
* @return TRUE if the queue is empty, otherwise FALSE
*/

template<typename T>
bool Queue<T>::isEmpty() const
{
	return List<T>::isEmpty();
}
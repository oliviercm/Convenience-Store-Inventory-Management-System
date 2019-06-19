/********************************************************************************
************************************ List ***************************************
*********************************************************************************
* Author: Olivier Chan - 50%
* Author: Luis Guerrero - 50%
*
* The purpose of this class is to provide a List ADT.
*****************
***** USAGE *****
*****************
* Use this class as a general purpose linked list.
* Keep in mind that this linked list only stores references to data.
* 
* Add data with insert(), insertFirst(), and insertLast().
* Remove data with remove(), removeFirst(), and removeLast().
* Access data references with List[index] or alternatively List.getData(index)
*********************************************************************************/

#pragma once

#include <iostream>

#include "Node.h"
#include  "Efficiency.h"

template <typename U> class List;
template <typename U>
std::ostream& operator<<(std::ostream& os, List<U>& list)
{
	for (int i = 0; i < list.getCount(); i++)
	{
		os << list.getData(i) << std::endl;
	}

	return os;
}

template <typename T>
class List
{
protected:
	int count;
	Node<T>* head;
public:
	List();
	virtual ~List();

	List(const List&) = delete;
	virtual List& operator=(const List&) = delete;

	virtual bool isEmpty() const;
	virtual int getCount() const;
	virtual Node<T>* insert(T&, const int); //A number outside the range 0-(count - 1) will throw an std::out_of_range exception.
	virtual Node<T>* insertFirst(T&);
	virtual Node<T>* insertLast(T&);
	virtual void remove(const int); //A number outside the range 0-(count - 1) will throw an std::out_of_range exception.
	virtual void remove(const T&);
	virtual void removeFirst();
	virtual void removeLast();
	virtual void removeAll();
	virtual T& getData(const int); //A number outside the range 0-(count - 1) will throw an std::out_of_range exception.
	virtual T& getFirstData();
	virtual T& getLastData();
	virtual void setData(T&, const int); //A number outside the range 0-(count - 1) will throw an std::out_of_range exception.
	virtual void setFirstData(T&);
	virtual void setLastData(T&);
	virtual void setData(T&&, const int); //A number outside the range 0-(count - 1) will throw an std::out_of_range exception.
	virtual void setFirstData(T&&);
	virtual void setLastData(T&&);

	virtual T& operator[](const int);
};

template <typename T>
List<T>::List() : count(0), head(nullptr)
{

}

template <typename T>
List<T>::~List()
{
	List::removeAll();
}

/*
Checks if the link-list is empty
@pre None
@post Checks if list is empty.
@return true if count is 0, otherwise false.
*/
template <typename T>
bool List<T>::isEmpty() const
{
	return count == 0;
}

/*
Gets the count of the link-list
@pre None
@post None
@return count.
*/
template <typename T>
int List<T>::getCount() const
{
	return count;
}

/*
Insert data into the list
@pre new reference data / position of the data
@post Checks if data can be entered / inserts data to the list
@return N/A.
*/
template <typename T>
Node<T>* List<T>::insert(T& newData, const int pos)
{
	if (pos < 0 || pos > count)
	{
		throw std::out_of_range("Index out of range.");
	}

	Node<T>* returnNode;

	if (head == nullptr) //The list is empty
	{
		head = new Node<T>(newData);
		Efficiency::globalListOperations++;

		returnNode = head;
	}
	else if (pos == 0) //Replacing head
	{
		Node<T>* temp = head;
		head = new Node<T>(newData, temp);
		Efficiency::globalListOperations++;

		returnNode = head;
	}
	else
	{
		Node<T>* currentNode = head;
		for (int i = 0; i < pos - 1; i++)
		{
			currentNode = currentNode->next;
			Efficiency::globalListOperations++;
		}

		Node<T>* temp = currentNode->next;
		currentNode->next = new Node<T>(newData, temp);
		Efficiency::globalListOperations++;

		returnNode = currentNode->next;
	}

	count++;
	return returnNode;
}

/*
Inserts data in the first position of the list
@pre New data that need to be inserted
@post Inserts the data to the first place
@return.
*/
template <typename T>
Node<T>* List<T>::insertFirst(T& newData)
{
	return insert(newData, 0);
}

/*
Inserts data at the last position of the list
@pre New data that needs to be added
@post Insert the data in the last position
@return.
*/
template <typename T>
Node<T>* List<T>::insertLast(T& newData)
{
	return insert(newData, count);
}

/*
Remove data from the list
@pre Position has to be less than 0 or greater than count -1.
@post Checks if data can be removed / remove the data from the position entered
@return.
*/
template <typename T>
void List<T>::remove(const int pos)
{
	if (head == nullptr) //The list is empty
	{
		throw std::out_of_range("List is empty.");
	}

	if (pos < 0 || pos > count - 1)
	{
		throw std::out_of_range("Index out of range.");
	}

	if (pos == 0)
	{
		Node<T>* nextNode = head->next;

		delete head;
		Efficiency::globalListOperations++;
		head = nextNode;
	}
	else
	{
		Node<T>* previousNode = nullptr;
		Node<T>* currentNode = head;
		for (int i = 0; i < pos; i++)
		{
			previousNode = currentNode;
			currentNode = currentNode->next;
			Efficiency::globalListOperations++;
		}

		previousNode->next = currentNode->next;

		delete currentNode;
		Efficiency::globalListOperations++;
	}

	count--;
	return;
}

template <typename T>
void List<T>::remove(const T& dataToRemove)
{
	if (head == nullptr) //The list is empty
	{
		throw std::out_of_range("List is empty.");
	}

	Node<T>* currentNode = head;
	for (int i = 0; i < count; i++)
	{
		if (currentNode->data == dataToRemove)
		{
			remove(i);
			return;
		}
		else
		{
			currentNode = currentNode->next;
			Efficiency::globalListOperations++;
		}
	}

	throw std::invalid_argument("Data to remove does not exist.");
}

/*
Removes the first element of the list
@pre None
@post Remove the first element
@return.
*/
template <typename T>
void List<T>::removeFirst()
{
	remove(0);
	return;
}

/*
Removes the last element
@pre None.
@post Remove the last elemnt of the list
@return.
*/
template <typename T>
void List<T>::removeLast()
{
	remove(count - 1);
	return;
}

/*
Removes all the list
@pre None.
@post Checks if list is empty / removes all the list
@return.
*/
template <typename T>
void List<T>::removeAll()
{
	if (head == nullptr) //The list is empty
	{
		return;
	}
	else
	{
		Node<T>* currentNode = head;
		while (currentNode->next != nullptr)
		{
			Node<T>* previousNode = currentNode;
			currentNode = currentNode->next;
			delete previousNode;
			Efficiency::globalListOperations++;
		}

		delete currentNode;
		Efficiency::globalListOperations++;
	}

	count = 0;
	head = nullptr;

	return;
}

/*
Gets data from the list
@pre Position
@post Gets the data from the position entered.
@return ptr of the current data.
*/

template <typename T>
T& List<T>::getData(const int pos)
{
	if (head == nullptr) //The list is empty
	{
		throw std::out_of_range("List is empty.");
	}

	if (pos < 0 || pos > count - 1)
	{
		throw std::out_of_range("Index out of range.");
	}

	Node<T>* currentNode = head;
	for (int i = 0; i < pos; i++)
	{
		currentNode = currentNode->next;
		Efficiency::globalListOperations++;
	}

	Efficiency::globalListOperations++;
	return currentNode->data;
}

/*
Gets data from the first element.
@pre None.
@post Gets the first element.
@return The data from the first element on the list.
*/

template <typename T>
T& List<T>::getFirstData()
{
	return getData(0);
}

/*
Gets data from the last element.
@pre None.
@post Gets the last element.
@return The data from the last element on the list.
*/

template <typename T>
T& List<T>::getLastData()
{
	return getData(count - 1);
}

/*
Sets data in the list.
@pre New Data / position.
@post Checks if data can be eneter / sets the new data to position.
@return.
*/
template <typename T>
void List<T>::setData(T& newData, const int pos)
{
	if (head == nullptr) //The list is empty
	{
		throw std::out_of_range("List is empty.");
	}

	if (pos < 0 || pos > count - 1)
	{
		throw std::out_of_range("Index out of range.");
	}

	Node<T>* currentNode = head;
	for (int i = 0; i < pos; i++)
	{
		currentNode = currentNode->next;
		Efficiency::globalListOperations++;
	}

	currentNode->data = newData;
	Efficiency::globalListOperations++;
	return;
}
template <typename T>
void List<T>::setData(T&& newData, const int pos)
{
	if (head == nullptr) //The list is empty
	{
		throw std::out_of_range("List is empty.");
	}

	if (pos < 0 || pos > count - 1)
	{
		throw std::out_of_range("Index out of range.");
	}

	Node<T>* currentNode = head;
	for (int i = 0; i < pos; i++)
	{
		currentNode = currentNode->next;
		Efficiency::globalListOperations++;
	}

	currentNode->data = std::move(newData);
	Efficiency::globalListOperations++;
	return;
}

/*
Sets data of the first element.
@pre New data.
@post Changes the fist element.
@return.
*/
template <typename T>
void List<T>::setFirstData(T& newData)
{
	setData(newData, 0);
}
template <typename T>
void List<T>::setFirstData(T&& newData)
{
	setData(std::move(newData), 0);
}

/*
Sets data of the last element.
@pre New data.
@post Changes the last element.
@return.
*/
template <typename T>
void List<T>::setLastData(T& newData)
{
	setData(newData, count - 1);
}

template <typename T>
void List<T>::setLastData(T&& newData)
{
	setData(std::move(newData), count - 1);
}

template <typename T>
T& List<T>::operator[](const int index)
{
	return getData(index);
}
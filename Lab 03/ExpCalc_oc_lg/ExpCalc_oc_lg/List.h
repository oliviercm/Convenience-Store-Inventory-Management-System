#pragma once

#include <iostream>

#include "Node.h"

template <typename U> class List;
template <typename U>
std::ostream& operator<<(std::ostream& os, List<U> list)
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

	bool isEmpty();
	int getCount();
	Node<T>* insert(T&, int); //A number outside the range 0-count will return nullptr! Insertion pushes both the element in the desired position and all elements after that element to the right.
	Node<T>* insertFirst(T&);
	Node<T>* insertLast(T&);
	void remove(int); //A number outside the range 0-(count - 1) will fail silently!
	void removeFirst();
	void removeLast();
	void removeAll();
	T& getData(int); //An invalid index will throw an exception.
	T& getFirstData();
	T& getLastData();
	void setData(T&, int); //An invalid index will fail silently!
	void setFirstData(T&);
	void setLastData(T&);
};

template <typename T>
List<T>::List()
{
	count = 0;
	head = nullptr;
}

template <typename T>
List<T>::~List()
{
	
}

/*
Checks if the link-list is empty
@pre None
@post Checks if list is empty.
@return true if count is 0, otherwise false.
*/
template <typename T>
bool List<T>::isEmpty()
{
	if (count == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
Gets the count of the link-list
@pre None
@post None
@return count.
*/
template <typename T>
int List<T>::getCount()
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
Node<T>* List<T>::insert(T& newData, int pos)
{
	if (pos < 0 || pos > count)
	{
		return nullptr;
	}

	if (head == nullptr) //The list is empty
	{
		head = new Node<T>(newData);

		count++;
		return head;
	}
	else if (pos == 0) //Replacing head
	{
		Node<T>* temp = head;
		head = new Node<T>(newData, temp);

		count++;
		return head;
	}
	else
	{
		Node<T>* currentNode = head;
		for (int i = 0; i < pos - 1; i++)
		{
			currentNode = currentNode->next;
		}

		Node<T>* temp = currentNode->next;
		currentNode->next = new Node<T>(newData, temp);

		count++;
		return currentNode->next;
	}

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
@post Cheks if data can be remove / remove the data from the position entered
@return.
*/
template <typename T>
void List<T>::remove(int pos)
{
	if (pos < 0 || pos > count - 1)
	{
		return;
	}

	if (head == nullptr) //The list is empty
	{
		return;
	}
	else
	{
		if (pos == 0)
		{
			Node<T>* nextNode = head->next;

			delete head;
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
			}

			if (currentNode->next != nullptr)
			{
				Node<T>* temp = currentNode->next;
				previousNode->next = temp;
			}

			delete currentNode;
		}
	}

	count--;
	return;
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
		Node<T>* previousNode = nullptr;
		Node<T>* currentNode = head;
		while (currentNode->next != nullptr)
		{
			previousNode = currentNode;
			currentNode = currentNode->next;
			delete previousNode;
		}

		delete currentNode;
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
T& List<T>::getData(int pos)
{
	if (pos < 0 || pos > count - 1 || head == nullptr)
	{
		throw "Invalid index";
	}

	Node<T>* currentNode = head;
	for (int i = 0; i < pos; i++)
	{
		currentNode = currentNode->next;
	}

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
void List<T>::setData(T& newData, int pos)
{
	if (pos < 0 || pos > count - 1 || head == nullptr)
	{
		return;
	}

	Node<T>* currentNode = head;
	for (int i = 0; i < pos; i++)
	{
		currentNode = currentNode->next;
	}

	currentNode->data = newData;
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
	return;
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
	return;
}
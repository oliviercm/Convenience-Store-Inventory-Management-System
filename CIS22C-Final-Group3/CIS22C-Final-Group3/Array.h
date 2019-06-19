/********************************************************************************
*********************************** Array ***************************************
*********************************************************************************
* Author: Olivier Chan - 100%
* 
* The purpose of this class is act as a std::vector-like.
*****************
***** USAGE *****
*****************
* Declare Arrays with Array() or Array(size)
* Add new data to Arrays with Array.append(data)
* Access stored data with Array[index]
*********************************************************************************/

#pragma once

#include "Efficiency.h"
#include "List.h"

template <typename T>
class Array
{
protected:
	T* arr; //The array
	int capacity; //The total size of the array
	int size; //The number of assigned elements in the array

	void allocateArray(int); //Initial allocation of the array. Should only be used during construction.
	void reallocateArray(int); //Reallocation of the array. Used to change array capacity when required.
public:
	Array(); //Creates an array of size 0.
	Array(int); //Creates an array of size int.

	Array(const Array<T>&);

	~Array();

	/**
	* append
	*
	* @brief Adds the reference to the array. If the capacity is too small to contain the new data, the array will be expanded to the next power of 2 in size.
	*
	* @param The reference to add to the array.
	*/
	T& append(const T&);
	T& append(T&&);
	/**
	* remove
	*
	* @brief Removes the reference from the array. If the capacity will become more than one factor of 2 larger than required, the array will be downsized to the smallest power of 2 required to contain the data.
	*
	* @param The index of the reference to remove from the array.
	*/
	void remove(const int);
	/**
	* front
	*
	* @brief Returns the data at the front of the array. Equivalent to arr[0].
	*
	* @return The reference at index 0.
	*/
	T& front();
	const T& front() const;
	/**
	* back
	*
	* @brief Returns the data at the back of the array. Equivalent to arr[size].
	*
	* @return The reference at index size.
	*/
	T& back();
	const T& back() const;
	/**
	* operator[]
	*
	* @brief Returns the reference stored at index.
	*
	* @param The index of the reference to return.
	*
	* @return The reference stored at index.
	*/
	T& operator[](int);
	const T& operator[](int) const;
	/**
	* @brief Returns size.
	*/
	int getSize() const;
	/**
	* @brief Returns capacity.
	*/
	int getCapacity() const;

	static Array<T> buildArrayFromList(List<T>&);
};

template <typename T>
Array<T>::Array() : Array(0)
{

}

template <typename T>
Array<T>::Array(int sz)
{
	allocateArray(sz);
}

template <typename T>
Array<T>::Array(const Array<T>& arrToCopy) : capacity(arrToCopy.capacity), size(arrToCopy.size)
{
	arr = new T[capacity];
	Efficiency::globalArrayOperations++;

	for (int i = 0; i < size; i++)
	{
		arr[i] = arrToCopy[i];
	}
}

template <typename T>
Array<T>::~Array()
{
	delete[] arr;
	Efficiency::globalArrayOperations++;
}

template <typename T>
void Array<T>::allocateArray(int sz)
{
	if (sz < 0)
	{
		throw std::invalid_argument("Negative size.");
	}

	//Make the array size the smallest power of 2 necessary based on the requested size. If the requested size is already a power of 2, make the array size the next power of 2.
	capacity = 1;
	while (capacity <= sz)
	{
		capacity *= 2;
	}

	arr = new T[capacity];
	Efficiency::globalArrayOperations++;
}

template <typename T>
void Array<T>::reallocateArray(int sz)
{
	if (sz < 0)
	{
		throw std::invalid_argument("Negative size.");
	}

	//Create a new array to hold the old elements
	int newCapacity = 1;
	while (newCapacity <= sz)
	{
		newCapacity *= 2;
	}

	if (newCapacity < size)
	{
		throw std::invalid_argument("Insufficent size.");
	}

	capacity = newCapacity;
	T* newArray = new T[newCapacity];
	Efficiency::globalArrayOperations++;

	//Copy old elements into the new array
	for (int i = 0; i < size; i++)
	{
		newArray[i] = arr[i];
		Efficiency::globalArrayOperations++;
	}

	//Delete the old managed array and set the new array as our managed array
	delete[] arr;
	arr = newArray;
	Efficiency::globalArrayOperations++;
}

template <typename T>
T& Array<T>::append(const T& data)
{
	//Make the array larger if needed
	if (size + 1 > capacity)
	{
		reallocateArray(size + 1);
	}
	
	arr[size] = data;
	size++;
	Efficiency::globalArrayOperations++;

	return arr[size - 1];
}

template <typename T>
T& Array<T>::append(T&& data)
{
	//Make the array larger if needed
	if (size + 1 > capacity)
	{
		reallocateArray(size + 1);
	}

	arr[size] = data;
	size++;
	Efficiency::globalArrayOperations++;

	return arr[size - 1];
}

template <typename T>
void Array<T>::remove(const int index)
{
	if (index < 0 || index > size)
	{
		throw std::out_of_range("Out of range.");
	}
	
	for (int i = index; i < size - 1; i++)
	{
		arr[i] = arr[i + 1];
	}

	size--;
	Efficiency::globalArrayOperations++;
}

template <typename T>
T& Array<T>::front()
{
	if (size <= 0)
	{
		throw std::out_of_range("Out of range.");
	}

	Efficiency::globalArrayOperations++;
	return arr[0];
}
template <typename T>
const T& Array<T>::front() const
{
	if (size <= 0)
	{
		throw std::out_of_range("Out of range.");
	}

	Efficiency::globalArrayOperations++;
	return arr[0];
}

template <typename T>
T& Array<T>::back()
{
	if (size <= 0)
	{
		throw std::out_of_range("Out of range.");
	}

	Efficiency::globalArrayOperations++;
	return arr[size - 1];
}
template <typename T>
const T& Array<T>::back() const
{
	if (size <= 0)
	{
		throw std::out_of_range("Out of range.");
	}

	Efficiency::globalArrayOperations++;
	return arr[size - 1];
}

template <typename T>
T& Array<T>::operator[](int index)
{
	if (index < 0 || index >= size)
	{
		throw std::out_of_range("Out of range.");
	}

	Efficiency::globalArrayOperations++;
	return arr[index];
}
template <typename T>
const T& Array<T>::operator[](int index) const
{
	if (index < 0 || index >= size)
	{
		throw std::out_of_range("Out of range.");
	}

	Efficiency::globalArrayOperations++;
	return arr[index];
}

template <typename T>
int Array<T>::getSize() const
{
	return size;
}

template <typename T>
int Array<T>::getCapacity() const
{
	return capacity;
}

template <typename T>
Array<T> Array<T>::buildArrayFromList(List<T>& list)
{
	Array<T> newArray = Array<T>(list.getCount());

	for (int i = 0; i < list.getCount(); i++)
	{
		newArray.append(list[i]);
	}

	return std::move(newArray);
}

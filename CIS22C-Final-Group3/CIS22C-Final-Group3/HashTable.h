/**********************************************************************************
 *********************************** HashTable ************************************
 **********************************************************************************
 * Author: Hiren Rathod - 90% - Primary author
 * Author: Olivier Chan - 10% - Conversion to store references, use key/values
 *
 * This class serves as a hash table that provides a user with efficiency in insertion, removal, and searching.
 * It contains several ADT functions to allow the user to experience optimal functionality with their data.
 * In the real world, an emergency system would be benefitted by the use of a hash table due to the hash table's potential for speedy searches.
 * In an ideal case, this hash table can return a value within the table in O(1) time.
 * This hash table uses separate chaining as the collision resolution mechanism.
 * To combat an O(n) traversal, this hash table uses a rehashing function to resize the table.
 *****************
 **** USAGE ***
 *****************
 * Declare an object of type HashTable, using template initialization.
 * You may then call HashTable functions on the new HashTable object.
 * ADT Functionalities:
 - Add
 - isEmpty
 - Remove
 - Empty
 - Manipulate Data
 - Get essential information about the data and the ADT itself
 Keep in mind:
 * It's advised to avoid repeatedly entering the same data. In order to preserve the search efficiency of the table, the table will resize itself but newly allocated memory becomes wasted if it is not used.
 * Avoid attempts of removing or getting the number of operations used on data not present in the table.
 ********************************************************************************/

#pragma once
#ifndef Hash_h
#define Hash_h

#include "HashList.h"
#include "Item.h"

template<typename K, typename T> class HashTable;
template<typename K, typename T>
std::ostream& operator<<(std::ostream& os, HashTable<K, T>& hashTable)
{
	for (int i = 0; i < hashTable.getSize(); i++)
	{
		os << *hashTable.getListAtKey(i) << std::endl;
	}

	return os;
}

template<typename K, typename T>
class HashTable
{
private:
    //Pointer to array of Hashed lists
    HashList<K, T>* arr;
    //Size of table
    int size;
    //Num of items in the table
    int count;
    //Load factor with respect to the hash table
    double loadFactor;
    //number of nodes that are chained on the linked list...non O(1) traversal;
    int offTable;
    /*
     * genAlg
     *
     * brief: Function that generates the modulo algorithm for an integer value
     *
     * param: item - integer value that will be stored in table
     *
     * returns: index that serves as a hash address
     */
    int genAlg(int item);
    /*
     * genAlg
     *
     * brief: Function that generates the modulo algorithm for a double value
     *
     * param: item - double value that will be stored in table
     *
     * returns: index that serves as a hash address
     */
    int genAlg(double item);
    /*
     * genAlg
     *
     * brief: Function that generates the modulo algorithm for a char value
     *
     * param: item - char value that will be stored in table
     *
     * returns: index that serves as a hash address
     */
    int genAlg(char item);
    /*
     * genAlg
     *
     * brief: Function that generates the modulo algorithm/folding algorithm for a string value
     *
     * param: item - string value that will be stored in table
     *
     * returns: index that serves as a hash address
     *
     * note: Performs a specialized folding algorithm with each character of the string. genAlg function is replicated for all data types as modulo operations on string objects are not allowed.
     */
    int genAlg(std::string item);
    /*
     * reHash
     *
     * brief: Function that performs rehashing when the number of nodes in the table exceed the table size.
     */
    void reHash();
public:
    /*
     * HashTable
     *
     * brief: Default Constructor that initializes member attributes
     */
    HashTable();
    /*
     * getSize
     *
     * brief: Function that returns the size of the table
     *
     * returns: size
     */
    int getSize() const;
    /*
     * add
     *
     * brief: Function that adds an item/key to the table at a specific hash address
     *
     * param: key - key/value pair for better searching and handling of complex data types, item - value that will be stored in table
     *
     * returns: boolean value to represent success/failure
     */
    bool add(K key, T& value);
    /*
     * remove
     *
     * brief: Function that removes an item/key from the table at a specific hash address
     *
     * param: key - key/value pair for better searching and handling of complex data types, item - value that will be removed from the table
     *
     * returns: boolean value to represent success/failure
     */
    bool remove(const K key, const T& value);
    /*
     * calcLoadFactor
     *
     * brief: Function that calculates and return the load factor of the table at any given time
     *
     * returns: loadFactor
     */
    double calcLoadFactor() const;
    /*
     * getAddress
     *
     * brief: Wrapper function that calls the private genAlg functions as the data type of a key is determined
     *
     * param: item - value that will be stored in the table
     *
     * returns: valid hash address
     */
    int getAddress(K key);
    /*
     * empty
     *
     * brief: Function that empties the hash table of all entries
     */
    void empty();
    /*
     * isEmpty
     *
     * brief: Function that returns if the HashTable has any values
     *
     * returns: bool value representing if there are any values in the hash table
     */
    bool isEmpty();
    /*
     * getCount
     *
     * brief: Function that returns the number of nodes present in the table.
     *
     * returns: count
     */
    int getCount() const;
    /*
     * getNextPrime
     *
     * brief: Function that returns the next available primre number for hash function use.
     *
     * returns: prime number
     */
    int getNextPrime() const;
    /*
     * getOffTable
     *
     * brief: Function that returns nodes that aren't on a linked list with 1 node
     *
     * returns: offTable
     */
    int getOffTable() const;
    /*
     * getListAtKey
     *
     * brief: Function that returns a linked list of data values given based off the hash of the passed key.
     *
     * param: key - key associated with a value...generates hash address
     *
     * returns: Pointer to a linked list of data
     */
    HashList<K, T>* getListAtKey(K key);
    /*
     * ~HashTable
     *
     * brief: Destructor that empties the array of linked lists and deletes the array
     */
    ~HashTable();
};

template<typename K, typename T>
HashTable<K, T>::HashTable()
{
    //Member Variables initialized, size set to prime number
    size = 101;
    count = 0;
    arr = new HashList<K,T>[size];
    offTable = 0;
}

template<typename K, typename T>
int HashTable<K, T>::getSize() const
{
    //Size of table
    return size;
}

template<typename K, typename T>
int HashTable<K, T>::getCount() const
{
    //Number of nodes in table
    return count;
}

template<typename K, typename T>
double HashTable<K, T>::calcLoadFactor() const
{
    //Load Factor = table items / table size
    return ((double)count / size);
}

template<typename K, typename T>
bool HashTable<K, T>::add(K key, T& item)
{
	int index = getAddress(key);
    //Shows numbers of extraneous nodes linked in the list...non-O(1) traversal
	if (!(arr + index)->isEmpty())
		offTable++;
    //Calls hash function and stores at beginning of the list at computed index
    (arr + index)->insertFirst(key, item);
	Efficiency::globalHashOperations++;
    //Increments number of nodes
    count++;
    //If load factor becomes greater than 75%
    if (calcLoadFactor() > 0.75)
        reHash(); //Rehashing
    return true;
}

template<typename K, typename T>
bool HashTable<K, T>::remove(const K key, const T& value)
{
	//Get hash address
    int index = getAddress(key);
    //Finds specific item's location in the list
    int position = (arr + index)->getPos(value);
    if (position == -1)
        return false;
    //Removes it from list
    (arr + index)->remove(position);
	Efficiency::globalHashOperations++;
    if ((arr + index)->getCount() >= 1)
        offTable--;
    //Decrement Count
    count--;
    return true;
}

template<typename K, typename T>
int HashTable<K, T>::getAddress(K item)
{
	Efficiency::globalHashOperations++;
	//Passes item to a genAlg function when data type of item is determined and returns a hash address
    return genAlg(item);
}


template<typename K, typename T>
int HashTable<K, T>::genAlg(int item)
{
    //Return hash address
    return(static_cast<int>(item) % size);
}

template<typename K, typename T>
int HashTable<K, T>::genAlg(double item)
{
    //Return hash address
    return(static_cast<int>(item) % size);
}

template<typename K, typename T>
int HashTable<K, T>::genAlg(char item)
{
    //Return hash address
    return(static_cast<int>(item) % size);
}


template<typename K, typename T>
int HashTable<K, T>::genAlg(std::string item)
{
    //Performs folding for string items
    int holder = 0;
    for (int i = 0; i < item.size(); i++)
    {
        //Folding each character
        holder += (int)item[i];
    }
    //Return hash address
    return (holder % size);
}

template<typename K, typename T>
int HashTable<K, T>::getOffTable() const
{
	//Return nodes off the table
    return offTable;
}

template<typename K, typename T>
void HashTable<K, T>::reHash()
{
	Efficiency::globalHashOperations++;
	//Temporary array with size of table
    const int prevSize = size;
	HashList<K, T>* prevArr = new HashList<K, T>[size];
    //Stores all linked lists in a temporary copy
    for (int i = 0; i < size; i++)
    {
        while (!(arr + i)->isEmpty())
        {
            //Storing data and keys into their respective arrays
			(prevArr + i)->insertFirst((arr + i)->getFirstKey(), (arr + i)->getFirstData());
            //Removing processed node from the linked list
            (arr + i)->removeFirst();
        }
    }
    //Multiplying size by 2
    size *= 2;
    //Getting the next available prime number
    size = getNextPrime();
    //Resetting count to 0
    count = 0;
    offTable = 0;
    //deleting array
    delete[] arr;
    //Redeclaring arr as a new pointer to an array of linked lists with updated size
    arr = new HashList<K, T>[size];
    //Reinserting all nodes back into the updated array
	for (int i = 0; i < prevSize; i++)
	{
		while (!(prevArr + i)->isEmpty())
		{
			add(prevArr[i].getFirstKey(), prevArr[i].getFirstData());
			//Removing processed node from the linked list
			(prevArr + i)->removeFirst();
		}
	}
    //deleting the temporary array
    delete[] prevArr;
}

template<typename K, typename T>
bool HashTable<K, T>::isEmpty()
{
	//Returns number of nodes present in the table
    return (count == 0);
}

template<typename K, typename T>
void HashTable<K, T>::empty()
{
	//Count set to zero
    count = 0;
    //Remove all elements of linked list across all indexes
    for (int i = 0; i < size; i++)
    {
        if (!(arr + i)->isEmpty())
            (arr + i)->removeAll();
    }
	Efficiency::globalHashOperations++;
}

template<typename K, typename T>
HashTable<K, T>::~HashTable()
{
    //Empty all linked lists of nodes
    empty();
    //Delete the array
    arr = 0;
    delete[] arr;
	Efficiency::globalHashOperations++;
}

template<typename K, typename T>
HashList<K, T>* HashTable<K, T>::getListAtKey(K key)
{
	Efficiency::globalHashOperations++;
	int index = getAddress(key);
    return arr + index;
}

template<typename U, typename V>
std::ostream& operator<<(std::ostream& os, const HashTable<U, V> & table)
{
    //Printing the table
    for (int i = 0; i < table.size; i++)
    {
        os << "Index: " << i << " ";
        if (!(table.arr + i)->isEmpty())
            os << *(table.arr + i);
        else
            os << std::endl;
    }
    return os;
}

//Returning the next available prime number
template<typename K, typename T>
int HashTable<K, T>::getNextPrime() const
{
	bool flag = true;
    int n = size + 1;
    while (flag)
    {
        for (int i = 2; i < n; i++)
        {
            if (n % i == 0)
            {
                flag = false;
            }
        }
        if (flag)
            n++;
    }
    return n;
}

#endif //Hash_h
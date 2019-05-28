#ifndef List_h
#define List_h
#include "Node.h"
#include <iostream>
template<typename L>
class List
{
private:
    int count;
    Node<L>* head;
    Node<L>* tail;
public:
    //Default Constructor
    List();
    //Destructor
    ~List();
    /*
     This function empties the entire linked list.
     Pre - A Linked List that contains an arbitrary amount of values.
     Post - A Linked List that is emptied out and contains no values.
     Returns: N/A
     */
    void empty();
    /*
     This function inserts a node at the beginning of the list.
     Pre - A Linked List consisting of values with a size.
     Post - A Linked List consisting of values with size + 1. The inserted value is located at the head of the linked list.
     Returns - N/A
     */
    void insertFirst(L&);
    /*
     This function inserts a node at the end of the list.
     Pre - list without insertion
     Post - list with insertion
     Returns - N/A
     */
    void insertLast(L&);
    /*
     This function removes a node at the beginning of the list.
     Pre - list without deletion
     Post - list with deletion
     Returns - N/A
     */
    void removeFromFront();
    /*
     This function inserts a node at a location in the list.
     Pre - list without insertion
     Post - list with insertion
     Returns - N/A
     */
    void insert(L&, int location);
    /*
     This function removes a node at a location in the list.
     Pre - list without deletion
     Post - list with deletion
     Returns - N/A
     */
    void remove(int location);
    /*
     This function checks to see if there are nodes in the linked list.
     Pre - N/A
     Post - N/A
     Returns - Returns whether list is empty or not
     */
    bool isEmpty();
    /*
     This function returns count of nodes.
     Pre - N/A
     Post - N/A
     Returns - Returns count of nodes.
     */
    int getCount();
    /*
     This function checks to see if there is a user desired node in the linked list.
     Pre - N/A
     Post - N/A
     Returns - Returns whether it is in the list
     */
    bool search(const L&);
    /*
     This function returns pointer to a node
     Pre - N/A
     Post - N/A
     Returns - Returns the pointer
     */
    Node<L> *getNewNode(L &);
    /*
     This function removes a node at the end of the list.
     Pre - list without deletion
     Post - list with deletion
     Returns - N/A
     */
    void removeFromBack();
    /*
     This function returns a pointer to a value at the head of the list.
     Returns - Pointer to data at head of the list.
     */
    L *getHeadData();
    /*
     This function returns a pointer to a value at the tail of the list.
     Returns - Pointer to data at tail of the list.
     */
    L *getTailData();
    //Overloaded Extraction operator for printing
    template<typename U>
    friend std::ostream & operator<<(std::ostream &, const List<U> &);
    //Will instantiate objects of Out_of_bounds to be thrown for invalid indexes
    class Out_of_bounds
    {
        int Olocation = 0;
    };
    
};



template<typename L>
List<L>::List()
{
    //Sets Pointers
    head = tail = 0;
    count = 0;
}
template<typename L>
bool List<L>::isEmpty()
{
    //Returns true if and only if head and tail pointers are NULL
    return (head == NULL && tail == NULL);
}
template<typename L>
void List<L>::insertFirst(L& value)
{
    //Creating a new pointer to a node for the passed value
    Node<L> *newPtr = getNewNode(value);
    //Checks if list is empty
    if (isEmpty())
        //Sets both head and tail pointers to the newPtr as it is the only node in the list
        head = tail = newPtr;
    else
    {
        //Moves the head to the newPtr's next pointer
        newPtr->next = head;
        //The new pointer now becomes the head
        head = newPtr;
    }
    //Increments number of nodes in list
    count++;
    //Deleting temporary pointer
    newPtr = nullptr;
    delete newPtr;
}

template<typename L>
void List<L>::insert(L& value, int location)
{
    Node<L> *currentPtr = head;
    //Creating a new pointer to a node for the passed value
    Node<L> *newPtr = getNewNode(value);
    //Range Validation
    if (location > count + 1 || location < 1)
    {
        //Throws an exception if passed location variable goes out of bounds
        throw List<L>::Out_of_bounds();
    }
    else
    {
        if (location == 1)
            //Inserts at beginning of list if location is one
            insertFirst(value);
        else if (location == count + 1)
            //Inserts at end of list if location is 1 more than count
            insertLast(value);
        else
        {
            //Traversing the list to the desired location
            for (int i = 1; i < location - 1; i++)
            {
                currentPtr = currentPtr->next;
            }
            //The current pointer's next becomes new pointer's next
            newPtr->next = currentPtr->next;
            //The new pointer is assigned to current pointer's next
            currentPtr->next = newPtr;
            //Increments number of nodes in list
            count++;
        }
    }
    //Deleting temporary pointers
    currentPtr = nullptr;
    newPtr = nullptr;
    delete currentPtr;
    delete newPtr;
}

template<typename L>
void List<L>::empty()
{
    //Happens until both pointers point to nothing
    while (head != 0 && tail != 0)
    {
        //Removing nodes from back of the list
        removeFromBack();
    }
    //Resetting count
    count = 0;
}

template<typename L>
int List<L>::getCount()
{
    //Getter function that returns the number of nodes in the list
    return count;
}

template<typename L>
Node<L> *List<L>::getNewNode(L &value)
{
    
    //This function recieves a value pointer and it is assigned to a new pointer which will be returned as a new Node.
    Node<L> *ptr = new Node<L>();
    //ptr's data pointer points to the address of value
    ptr->data = &value;
    //Returning the created pointer of Nodes
    return ptr;
}

// Insert a node at the back of the list
template< typename L >
void List< L >::insertLast(L &value)
{
    //Assigns passed value as the new pointer
    Node< L > *newPtr = getNewNode(value);
    if (isEmpty()) // List is empty
        //Makes the head and tail pointer equal the new pointer
        head = tail = newPtr;
    else // List is not empty
    {
        //The pointer after the original tail pointer becomes the new pointer
        tail->next = newPtr;
        //The new pointer becomes the new tail pointer
        tail = newPtr;
    }
    //Increments number of nodes in list
    count++;
    //Deleting temporary pointers
    newPtr = nullptr;
    delete newPtr;
}
// Delete a node from the front of the list
template< typename L >
void List< L >::removeFromFront()
{
    if (isEmpty()) // List is empty
        return; //unsuccessful
    else
    {
        if (head == tail)
            //The list is assigned the value of 0 if the head pointer is the same as the tail pointer
            head = tail = 0;
        else
            //The original head pointer becomes is assigned  to its next pointer
            head = head->next;
        //Decrements number of nodes in the list
        count--;
    }
    
}

template< typename L >
void List< L >::removeFromBack()
{
    if (isEmpty()) //list is empty
        return; // delete unsuccessful
    else
    {
        //A temporary pointer that is assigned the value of the tail pointer
        Node<L> *tempPtr = tail;
        if (head == tail)
            //The list is assigned the value of 0 if the first pointer is the same as the last pointer
            head = tail = 0;
        else
        {
            //A current pointer is created to point to the head pointer
            Node<L> *currentPtr = head;
            //Traversing the list until the end
            while (currentPtr != tail)
            {
                if(currentPtr -> next == tail)
                    tempPtr = currentPtr;
                //While the next pointer isn't equal to the tail pointer, the linked list will be traversed
                currentPtr = currentPtr->next;
            }
            //Once the end of the linked list is found, the tail pointer will equal the current pointer
            tail = tempPtr;
            //The next pointer will be assigned the value of NULL
            tempPtr->next = NULL;
            delete tempPtr; //Temporary current pointer is deleted
        }
        tempPtr = nullptr;
        //The temporary pointer becomes deleted
        delete tempPtr; //delete successful
        //Decrements number of nodes in the list
        count--;
    }
}
template<typename L>
bool List<L>::search(const L& value)
{
    bool found = false;
    //Creating a current pointer that points to the head of the list
    Node<L> *currentPtr = head;
    //Traverses the list until the value that is being searched is found
    while (currentPtr != 0 && found == false)
    {
        //Dereferencing the current pointer's data to see if it equals the value that is being searched
        if (*(currentPtr->data) == value)
        {
            //If the value is present on the list, it is found
            found = true;
        }
        //Traversing to the next node in the list
        currentPtr = currentPtr->next;
    }
    //Deleting temporary pointer
    currentPtr = nullptr;
    delete currentPtr;
    //Returning true if found, false if not found in list
    if (found)
        return true;
    else
        return false;
}

template <typename L>
void List<L>::remove(int location)
{
    //Current pointer that points to the head of the list
    Node<L> *currentPtr = head;
    //New pointer that points to nothing
    Node<L> *newPtr = nullptr;
    //Throws exception if passed location if out of bounds of the linked list
    if (location > count || location < 1)
        throw Out_of_bounds();
    else
    {
        //If the first element of the linked list needs to be removed.
        if (location == 1)
            removeFromFront();
        //If the location to be removed is equal to the size of the list
        else if (location == count)
            removeFromBack();
        else
        {
            //Traversing to the location that needs to be removed
            for (int i = 1; i < location; i++)
            {
                //newPtr is set to the node before the node that needs to be removed
                if (i == location - 1)
                    newPtr = currentPtr;
                //Traversing to the next node
                currentPtr = currentPtr->next;
            }
            //NewPtr's next pointer now points to what current pointer's next pointer points to
            newPtr->next = currentPtr->next;
            //Decrements number of nodes in list
            count--;
        }
    }
    //Deleting temporary pointers
    currentPtr = nullptr;
    newPtr = nullptr;
    delete currentPtr;
    delete newPtr;
}


template<typename L>
//Destructor
List<L>::~List()
{
    //Empties list
    empty();
    //Deleting head and tail pointers
    delete head;
    delete tail;
}

template<typename U>
//Overloaded Extraction Operator
std::ostream & operator << (std::ostream & strm, const List<U> & right)
{
    //Variables to be compared
    int i;
    double d;
    std::string s;
    char c;
    //Creating current pointer to point to the head of the list
    Node<U> *currentPtr = right.head;
    //Outputting the list
    strm << "The list is: " << std::endl;
    //Traverses the list until the end of the list
    while (currentPtr != right.tail -> next)
    {
        //Using data type comparisons as a result of poor overloaded extraction operator design in Lab1
        if (typeid(*(currentPtr->data)).name() == typeid(i).name() || typeid(*(currentPtr->data)).name() == typeid(d).name() || typeid(*(currentPtr->data)).name() == typeid(s).name() || typeid(*(currentPtr->data)).name() == typeid(c).name())
        {
            // data value is a simple data type and needs an end line
            strm << "Value: " << *(currentPtr->data) << std::endl;
        }
        else
        {
            //The data is of a data type that has an extraction operator that has an endline
            strm << "Value: " << *(currentPtr->data);
        }
        //Traversing to the next node in the list
        currentPtr = currentPtr->next;
    }
    //Attempting to print an empty list
    if (right.head == NULL)
        strm << "The container is empty. Add something." << std::endl;
    strm << std::endl;
    //Deleting temporary pointer
    currentPtr = nullptr;
    delete currentPtr;
    return strm;
}

template<typename L>
L* List<L>::getHeadData()
{
    //Returning the data pointer of the first element of the linked list
    return head -> data;
}

template<typename L>
L* List<L>::getTailData()
{
    //Returning the data pointer of the last element of the linked list
    return tail -> data;
}

#endif /* List_h */


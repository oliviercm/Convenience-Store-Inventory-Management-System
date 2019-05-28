

#ifndef Queue_h
#define Queue_h

#include "List.h"

template<typename Q>
class Queue : protected List<Q>
{
public:
    /*
     This function adds a value to the end of the queue. The rear is incremented by one.
     Pre - A queue of values consisting of a size.
     Post - A queue of values consisting of size + 1. The enqueued value is located at the rear of the queue.
     Returns - A boolean value depending on if the add to the end of the queue is successful.
     */
    bool enqueue(Q&);
    /*
     This function removes a value from the end of the queue and increments the front. This function also returns the dequeued value in case that data needs to be manipulated.
     Pre - A queue of values consisting of a size.
     Post - A queue of values consisting of size - 1. The dequeued value is removed from the front of the queue.
     Returns - A boolean value depending on if the dequeue is successful.
     */
    Q dequeue();
    /*
     This function checks to see if the queue is empty. If the queue is empty, then the function returns true.
     Returns - A boolean value depending on if the queue is empty.
     */
    bool isEmpty_queue();
    /*
     This function discards all values in the queue when called.
     Pre - Queue that contains values.
     Post - Queue that is emptied of all values.
     Returns - N/A
     */
    void clear_queue();
    /*
     This function returns the number of elements present in the queue when called.
     Returns - An integer that represents the size of the cue.
     */
    int size_queue();
    /*
     This function returns a pointer to the value that is located at the front of the queue.
     Returns - A pointer to the data at the front of the queue.
     */
    Q* queue_front();
    /*
     This function returns a pointer to the value that is located at the end of the queue.
     Returns - A pointer to the data at the end of the queue.
     */
    Q* queue_rear();
    //Destructor
    ~Queue();
    template<typename U>
    //Overloaded extraction operator to print a queue
    friend std::ostream & operator << (std::ostream & strm, const Queue<U> &);
    
};

template<typename Q>
bool Queue<Q>::enqueue(Q& value)
{
    //Calls the insertLast function of the Linked List class and passes the value that needs to be enqueued.
    List<Q>::insertLast(value);
    return true;
}

template<typename Q>
Q Queue<Q>::dequeue()
{
    //This statement dereferences a pointer to data at the front of the queue and stores it into the value variable.
    Q value = *(queue_front());
    //Calls the removeFromFront function of the Linked List class to remove the value at the front of the queue.
    List<Q>::removeFromFront();
    //The data at the front of the queue is returned.
    return value;
}

template<typename Q>
Q* Queue<Q>::queue_front()
{
    //Calls the getHeadData function of the Linked List class to return the data located at the front of the queue.
    return List<Q>::getHeadData();
}

template<typename Q>
Q* Queue<Q>::queue_rear()
{
    //Calls the getTailData function of the Linked List class to return the data located at the rear of the queue.
    return List<Q>::getTailData();
}

template<typename Q>
bool Queue<Q>::isEmpty_queue()
{
    //Calls the isEmpty function of the Linked List class to return whether the queue is empty or not.
    return List<Q>::isEmpty();
}

template<typename Q>
void Queue<Q>::clear_queue()
{
    //Calls the empty function of the Linked List class to empty the queue.
    List<Q>::empty();
}

template<typename Q>
int Queue<Q>::size_queue()
{
    //Calls the getCount function of the Linked List class to return the size of the queue.
    return List<Q>::getCount();
}

template<typename Q>
Queue<Q>::~Queue()
{}

template<typename Q>
//Overloaded extraction operator to print a queue
std::ostream & operator << (std::ostream & strm, const Queue<Q> & right)
{
    //Type-Casting the passed Queue to a List. This will call the overloaded operator in the Linked List class for printing.
    strm << (List<Q> &) right;
    return strm;
}
#endif /* Queue_h */

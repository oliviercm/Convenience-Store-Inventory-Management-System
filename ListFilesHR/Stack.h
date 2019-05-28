

#ifndef Stack_h
#define Stack_h
#include "List.h"

template <typename S>
class Stack : protected List<S>
{
public:
    void push(S& value);
    void pop();
    int size();
    bool isEmpty();
    void print();
    S* peek();
    template<typename U>
    //Overloaded extraction operator to print a queue
    friend std::ostream & operator << (std::ostream & strm, const Stack<U> &);
};

template <typename S>
void Stack<S>::push(S& value)
{
    List<S>::insertFirst(value);
}


template <typename S>
void Stack<S>::pop()
{
    List<S>::removeFromFront();
}


template<typename S>
bool Stack<S>::isEmpty()
{
    return List<S>::isEmpty();
}

template<typename S>
int Stack<S>::size()
{
    return List<S>::getCount();
}

template<typename S>
void Stack<S>::print()
{
    List<S>::print();
}

template<typename S>
S* Stack<S>::peek()
{
    if (size() > 0)
        return List<S>::getHeadData();
    else return NULL;
}

template<typename S>
//Overloaded extraction operator to print a queue
std::ostream & operator << (std::ostream & strm, const Stack<S> & right)
{
    //Type-Casting the passed Queue to a List. This will call the overloaded operator in the Linked List class for printing.
    strm << (List<S> &) right;
    return strm;
}

#endif /* Stack_h */


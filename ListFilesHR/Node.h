#ifndef Node_h
#define Node_h

template <typename T>
struct Node
{
    T* data;
    Node<T>* next;
    Node();
    Node<T>(T&);
    Node *getNextPtr();
    void setNext(Node*);
    ~Node();
};

template<typename T>
Node<T>::Node()
{
    next = 0;
}

//Constructor
template<typename T>
Node< T >::Node(T &info )
{
    /*
     This constructor recieves an info pointer and assigns it to the data variable. This constructor also initializes the nextPtr variable value to 0.
     Parameter: const T &info - Information that will be stored in the data variable
     */
    data = &info;
    next = 0;
}

template<typename T>
Node<T>* Node<T>::getNextPtr()
{
    return next;
}

template<typename T>
void Node<T>::setNext(Node* passed_ptr)
{
    next = passed_ptr;
}

template<typename T>
Node<T>::~Node()
{
    //delete data;
    delete next;
}

#endif /* Node_h */



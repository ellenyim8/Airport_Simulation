/*************************************************************
 * queue class
 * CONSTRUCTOR & DESTRUCTOR
 *      queue()
 *          - default CTOR, initialize an empty queue
 *      ~queue()
 *          - destructor; deletes queue
 *
 * ACCESSORS
 *      bool isEmpty() const
 *          - returns if queue is empty or not
 *      bool isFull() const
 *          - returns if queue is full or not
 *      int size() const
 *          - returns size of queue
 *      T Front() const;
 *          - returns the front node of the queue
 *      T Rear() const;
 *          - returns rear node of queue
 * MUTATORS
 *      void enqueue(T value)
 *          - pushes back the value to the back of the queue
 *      void dequeue()
 *          - pops the value from front of queue
 *
**************************************************************/
#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
using namespace std;

template <typename T>
class queue
{
private:
    class Node {
    public:
        T data;
        Node* next;
        Node(T value, Node* link = 0)
        {
            data = value;
            next = link;
        }
    };
    Node* _front;
    Node* _rear;

public:
    // CONSTRUCTORS & DESTRUCTOR
    queue();
    ~queue();

    // COPY CONSTRUCTOR
    queue(const queue& other);
    // ASSIGNMENT OPERATOR =
    const queue& operator =(const queue& other);

    // ACCESSORS
    bool isEmpty() const;
    bool isFull() const;
    int size() const;
    T Front() const;
    T Rear() const;

    // MUTATORS
    void enqueue(T value);
    void dequeue();
    void update_queue();

    void display(ostream& outs);
};


/*************************************************************
 * queue()
 *      - default constructor, initialize an empty queue
 * ----------------------------------------------------------
 *      Parameters: none
 * ----------------------------------------------------------
 *      Returns: none
**************************************************************/
template <typename T>
queue<T>::queue()
{
    _front = _rear = 0;
}

/*************************************************************
 * queue(const queue& original)
 *      - copy CTOR, copies member root and its attributes to
 *      another queue object.
 * ----------------------------------------------------------
 *      Parameters: queue&
 * ----------------------------------------------------------
 *      Returns: none
**************************************************************/
template <typename T>
queue<T>::queue(const queue& other)
{
    _front = _rear = 0;
    if (!other.isEmpty())
    {
        Node* temp = new Node(other.Front());
        _front = _rear = temp;
        Node* current = other._front->next;
        while (current != 0)
        {
            _rear->next = new Node(current->data);
            _rear = _rear->next;
            current = current->next;
        }
    }
}

/*************************************************************
 * ~queue()
 *      - destructor, goes through queue, deleting each element
 * ----------------------------------------------------------
 *      Parameters: none
 * ----------------------------------------------------------
 *      Returns: none
**************************************************************/
template <typename T>
queue<T>::~queue()
{
    Node* current = _front;
    Node* temp;

    while (current != NULL)
    {
        temp = current->next;
        delete current;
        current = temp;
    }
}

template <typename T>
const queue<T>& queue<T>::operator=(const queue &other)
{
    if (this == &other)
    {
        return *this;
    }

    this->~queue();
    if (other.isEmpty())
    {
        _front = _rear = 0;
    }
    else
    {
        Node* temp = new Node(other.Front());
        _front = _rear = temp;

        Node* current = other._front->next;
        while (current != 0)
        {
            _rear->next = new Node(current->data);
            _rear = _rear->next;
            current = current->next;
        }
    }
    return *this;
}

/*************************************************************
 * bool isEmpty() const
 *      Accessor; checks if queue is empty
 * ----------------------------------------------------------
 *      Parameters: none
 * ----------------------------------------------------------
 *      Returns: bool
**************************************************************/
template <typename T>
bool queue<T>::isEmpty() const
{
    return (_front == 0);
}

/*************************************************************
 * bool isFull() const
 *      Accessor; returns if queue is full
 * ----------------------------------------------------------
 *      Parameters: none
 * ----------------------------------------------------------
 *      Returns: bool
**************************************************************/
template <typename T>
bool queue<T>::isFull() const
{
    return (_rear == _front->next);
}

/*************************************************************
 * int size() const
 *      Accessor; returns the size of the queue
 * ----------------------------------------------------------
 *      Parameters: none
 * ----------------------------------------------------------
 *      Returns: int
**************************************************************/
template <typename T>
int queue<T>::size() const
{
    int size = 0;
    Node* current = _front;
    while (current != NULL)
    {
        size++;
        current = current->next;
    }
    return size;
}

/*************************************************************
 * T Front() const
 *      Accessor; returns the front node data value
 * ----------------------------------------------------------
 *      Parameters: none
 * ----------------------------------------------------------
 *      Returns: T (type)
**************************************************************/
template <typename T>
T queue<T>::Front() const
{
    if (!isEmpty())
        return _front->data;
    return _front->data = 0;
}

template <typename T>
T queue<T>::Rear() const
{
    if (!isFull())
        return _rear->data;
    return _rear->data = 0;
}

/*************************************************************
 * void enqueue(T value)
 *      Mutator; pushes back the given value to the back of
 *      the queue
 * ----------------------------------------------------------
 *      Parameters: value // IN: T value
 * ----------------------------------------------------------
 *      Returns: none
**************************************************************/
template <typename T>
void queue<T>::enqueue(T value)
{
    Node* newNode = new Node(value, NULL);

    if (newNode == 0)
    {
        printf("insufficient memory for new node. \n");
        exit(1);
    }
    if (isEmpty())
    {
        _front = newNode;
        _rear = newNode;
    }
    else
    {
        _rear->next = newNode;
        _rear = newNode;
    }
}

/*************************************************************
 * void dequeue()
 *      Mutator; pops back the front node value of the queue
 * ----------------------------------------------------------
 *      Parameters: none
 * ----------------------------------------------------------
 *      Returns: none
**************************************************************/
template <typename T>
void queue<T>::dequeue()
{
    if (!isEmpty())
    {
        Node* temp = _front;
        _front = _front->next;
        delete temp;

        if (_front == 0)
        {
            _rear = 0;
        }
    }
    else {
        printf("can't remove from empty queue. \n");
    }
}

/*************************************************************
 * void update_queue()
 *      Mutator; updates queue
 * ----------------------------------------------------------
 *      Parameters: none
 * ----------------------------------------------------------
 *      Returns: none
**************************************************************/
template <typename T>
void queue<T>::update_queue()
{
    Node* current = _front;
    while (current != NULL)
    {
        (current->data).update(); // update() in plane
        current = current->next;
    }
    return;
}

/*************************************************************
 * void display(ostream& outs)
 *      - displays the queue
 * ----------------------------------------------------------
 *      Parameters: ostream&
 * ----------------------------------------------------------
 *      Returns: none
**************************************************************/
template <typename T>
void queue<T>::display(ostream &outs)
{
    Node* current = _front;

    while (current != NULL)
    {
        outs << current->data << " ";
        current = current->next;
    }
    outs << endl;
}



#endif // QUEUE_H

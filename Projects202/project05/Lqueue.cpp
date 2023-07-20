/*****************************************************************************
 ** File: Lqueue.cpp
 ** Project: CMSC 202 Project 5, Spring 2022
 ** Author:  Eric Ekey
 ** Section: 52
 ** Date:    05/01/2022
 ** Email:   eekey1@gl.umbc.edu
 **
 Description: CPP file for Lqueue class. Includes both class definition and
 class function definitions.
*****************************************************************************/

#ifndef LQUEUE_CPP
#define LQUEUE_CPP
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//Templated node class used in templated linked list
template <class T>
class Node {
   public:
  Node( const T& data ); //Constructor
  T& GetData(); //Gets data from node
  void SetData( const T& data ); //Sets data in node
  Node<T>* GetNext(); //Gets next pointer
  void SetNext( Node<T>* next ); //Sets next pointer
private:
  T m_data;
  Node<T>* m_next;
};

//Overloaded constructor for Node
template <class T>
Node<T>::Node( const T& data ) {
   m_data = data;
   m_next = NULL;
}

//Returns the data from a Node
template <class T>
T& Node<T>::GetData() {
   return m_data;
}

//Sets the data in a Node
template <class T>
void Node<T>::SetData( const T& data ) {
   m_data = data;
}

//Gets the pointer to the next Node
template <class T>
Node<T>* Node<T>::GetNext() {
   return m_next;
}

//Sets the next Node
template <class T>
void Node<T>::SetNext( Node<T>* next ) {
   m_next = next;
}

template <class T>
class Lqueue {
 public:
  // Name: Lqueue() (Linked List Queue) - Default Constructor
  // Desc: Used to build a new linked queue (as a linked list)
  // Preconditions: None
  // Postconditions: Creates a new lqueue where m_head and m_tail point to nullptr
  // Required
  Lqueue();
  // Name: ~Lqueue() - Destructor
  // Desc: Used to destruct a Lqueue
  // Preconditions: There is an existing lqueue with at least one node
  // Postconditions: An lqueue is deallocated (including dynamically allocated nodes)
  //                 to have no memory leaks!
  // Required
 ~Lqueue();
  // Name: Lqueue (Copy Constructor)
  // Preconditions: Creates a copy of existing LQueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  // Required
  Lqueue(const Lqueue&);
  // Name: operator= (Overloaded Assignment Operator)
  // Preconditions: Copies an Lqueue into an existing Lqueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  // Required
  Lqueue<T>& operator= (Lqueue&);
  // Name: Push
  // Preconditions: Takes in data. Creates new node. 
  //                Requires a Lqueue
  // Postconditions: Adds a new node to the end of the lqueue.
  // Required
  void Push(const T&);
  // Name: Pop
  // Preconditions: Lqueue with at least one node. 
  // Postconditions: Removes first node in the lqueue, returns data from first node.
  // Required
  T Pop();
  // Name: Display
  // Preconditions: Outputs the lqueue.
  // Postconditions: Displays the data in each node of lqueue
  // Required (used only for testing)
  void Display();
  // Name: Front
  // Preconditions: Requires a populated lqueue
  // Postconditions: Returns whatever data is in front
  // Required
  T Front();
  // Name: IsEmpty
  // Preconditions: Requires a lqueue
  // Postconditions: Returns if the lqueue is empty.
  // Required
  bool IsEmpty();
  // Name: GetSize
  // Preconditions: Requires a lqueue
  // Postconditions: Returns m_size
  // Required
  int GetSize();
  // Name: Find()
  // Preconditions: Requires a lqueue
  // Postconditions: Iterates and if it finds the thing, returns index, else -1
  // Required
  int Find(T&);
  // Name: Swap(int)
  // Preconditions: Requires a lqueue
  // Postconditions: Swaps the nodes at the index with the node prior to it.
  // Required
  void Swap(int);
  // Name: Clear
  // Preconditions: Requires a lqueue
  // Postconditions: Removes all nodes in a lqueue
  // Required
  void Clear();
  // Name: At
  // Precondition: Existing Lqueue
  // Postcondition: Returns object from Lqueue at a specific location
  // Desc: Iterates to node x and returns data from Lqueue
  // Required
  T At (int x);
private:
  Node <T> *m_head; //Node pointer for the head
  Node <T> *m_tail; //Node pointer for the tail
  int m_size; //Number of nodes in queue
};

//**********Implement Lqueue Class Here***********
//**********All Functions Are Required Even If Not Used for Trivia**************


// Name: Lqueue() (Linked List Queue) - Default Constructor
// Desc: Used to build a new linked queue (as a linked list)
template <class T>
Lqueue<T>::Lqueue() {
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}


// Name: ~Lqueue() - Destructor
// Desc: Used to destruct a Lqueue
template <class T>
Lqueue<T>::~Lqueue() {
    // delete nodes in queue
    Clear();
}


// Name: Lqueue (Copy Constructor)
// Desc: Creates a copy of existing LQueue
template <class T>
Lqueue<T>::Lqueue(const Lqueue& aLinkedList) {
    Node<T>* curr = aLinkedList.m_head; // node pointer to current node in passed queue

    // fill new queue with nodes from passed queue
    while (curr != nullptr) {
        Push(curr->GetData());
        curr = curr->GetNext();
    }
}


// Name: operator= (Overloaded Assignment Operator)
// Desc: Copies an Lqueue into an existing Lqueue
template <class T>
Lqueue<T>& Lqueue<T>::operator= (Lqueue& aLinkedList) {
    Node<T>* curr = aLinkedList.m_head; // node pointer to current node in passed queue

    // clear the queue and refill with nodes from passed queue
    Clear();
    while (curr != nullptr) {
        Push(curr->GetData());
        curr = curr->GetNext();
    }
    return *this;
}


// Name: Push
// Desc: Takes in data. Creates new node.
template <class T>
void Lqueue<T>::Push(const T& aData) {
    Node<T>* newNode = new Node<T>(aData);  // node pointer to dynamically allocated new node

    // add node to end of queue
    if (IsEmpty()) {
        m_head = newNode;
        m_tail = newNode;
        m_size = 1;
    } else {
        m_tail->SetNext(newNode);
        m_tail = newNode;
        newNode->SetNext(nullptr);
        m_size++;
    }
}



// Name: Pop
// Desc: Removes first node in the lqueue, returns data from first node.
template <class T>
T Lqueue<T>::Pop() {
    Node<T>* curr = m_head; // node pointer to current node
    Node<T>* next = curr->GetNext();    // node pointer to next node
    T currData = Front();   // data in first node of queue

    //  remove the first node in the queue
    if (!IsEmpty()) {
        delete curr;
        curr = nullptr;
        m_head = next;
        m_size--;
    }
    return currData;
}


// Name: Display
// Desc: Outputs the lqueue and the data in each node
template <class T>
void Lqueue<T>::Display() {
    Node<T>* curr = m_head; // node pointer to current node
    int index = 0;    // indexes for labeling list

    // output index numbered list of data in each node
    if (!IsEmpty()) {
        while (curr != nullptr) {
            cout << index << ". " << curr->GetData() << "\n";
            curr = curr->GetNext();
            index++;
        }
    }
}


// Name: Front
// Desc: Returns whatever data is in front of the Lqueue
template <class T>
T Lqueue<T>::Front() {
    T frontData = m_head->GetData();    // data in the first node of the queue
    return frontData;
}


// Name: IsEmpty
// Desc: Returns if the lqueue is empty.
template <class T>
bool Lqueue<T>::IsEmpty() {
    bool isEmpty = (GetSize() == 0);    // whether the queue is empty
    return isEmpty;
}


// Name: GetSize
// Desc: returns size of Lqueue
template <class T>
int Lqueue<T>::GetSize() {
    return m_size;
}


// Name: Find()
// Desc: Returns index data passed to it is found at
template <class T>
int Lqueue<T>::Find(T& aData) {
    Node<T>* curr = m_head; // node pointer to current node
    T currData = curr->GetData();   // data in current node
    int index = 0;  // index tracker

    // look through the queue until you find the target data
    while (index < GetSize()) {
        currData = curr->GetData();
        if (currData == aData) {
            return index;
        }
        curr = curr->GetNext();
        index++;
    }
    return -1;
}


// Name: Swap(int)
// Desc: Swaps the nodes at the index with the node prior to it.
template <class T>
void Lqueue<T>::Swap(int aIndex) {
    Node<T>* curr = m_head; // node pointer to current node
    Node<T>* prev = nullptr;    // node pointer to previous node
    Node<T>* next = nullptr;    // node pointer to next node
    int index = 1;  // index tracker

    if (GetSize() > 1 && index <= aIndex) {
        // move to the relevant section of the queue
        next = curr->GetNext();
        while (index < aIndex) {
            prev = curr;
            curr = curr->GetNext();
            next = curr->GetNext();
            index++;
        }
        // reshuffle links to swap curr and next
        if (prev != nullptr) {
            prev->SetNext(next);
        }
        curr->SetNext(next->GetNext());
        next->SetNext(curr);

        // redefine head and tail if needed
        if (m_head == curr) {
            m_head = next;
        }
        if (m_tail == next) {
            m_tail = curr;
        }
    }
}


// Name: Clear
// Desc: Removes all nodes in a lqueue
template <class T>
void Lqueue<T>::Clear() {
    if (!IsEmpty()) {
        Node<T>* curr = m_head; // node pointer to current node
        Node<T>* prev = nullptr;    // node pointer to previous node

        // delete nodes in queue
        while (curr != nullptr) {
            prev = curr;
            curr = curr->GetNext();
            delete prev;
            m_size--;
        }
        prev = nullptr;
    }
}


// Name: At
// Desc: Returns object from Lqueue at a specific location
template <class T>
T Lqueue<T>::At (int aIndex) {
    Node<T>* curr = m_head; // node pointer to iterate queue
    T currData = curr->GetData();   // data at curr node
    int i = 0;  // counter

    // move curr along queue until it reaches target index
    if (i <= aIndex) {
        while (i < aIndex) {
            curr = curr->GetNext();
            currData = curr->GetData();
            i++;
        }
    }
    return currData;
}


#endif

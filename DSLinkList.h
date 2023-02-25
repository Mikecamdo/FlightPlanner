//
// Created by mikec_g1kgiu8 on 10/19/2021.
//

#ifndef INC_21F_FLIGHT_PLANNER_DSLINKLIST_H
#define INC_21F_FLIGHT_PLANNER_DSLINKLIST_H

#include "DSListNode.h"
#include <iostream>

template <typename T>
class DSLinkList {
    private:
        //Pointers To Nodes
        DSListNode<T>* head;
        DSListNode<T>* tail;
        DSListNode<T>* curr;

    public:
        //Constructors/Destructor
        DSLinkList();
        DSLinkList(const DSLinkList&);
        ~DSLinkList();

        //Overloaded Operator
        DSLinkList& operator=(const DSLinkList&);

        //Functions
        void add(T);
        void removeLast();
        T getLastData();
        bool isEmpty();

        //Iterating Functions
        void setCurrHead();
        void advanceCurr();
        void fallBackCurr();
        T& getCurrValue();
        bool hasNext();
        bool currIsNull();
};

template<typename T>
DSLinkList<T>::DSLinkList() { //default constructor
    head = nullptr;
    tail = nullptr;
}

template<typename T>
DSLinkList<T>::DSLinkList(const DSLinkList<T>& arg) { //copy constructor
    if (arg.head == nullptr) { //if the LinkList is empty
        head = nullptr;
        tail = nullptr;
    } else {
        head = new DSListNode<T>;
        head->setData(arg.head->getData()); //create and set the head node

        DSListNode<T>* argCurrent = arg.head;
        if (argCurrent->getNext() == nullptr) { //if the Linked List has only 1 element
            tail = head; //set tail to head
        } else { //if the Linked List has more than 1 element
            while (argCurrent->getNext() != nullptr) { //create and add nodes to the Linked List (with the other Linked List's data)
                argCurrent = argCurrent->getNext();
                this->add(argCurrent->getData());
            }
        }
    }
}

template<typename T>
DSLinkList<T>::~DSLinkList() { //destructor
    DSListNode<T>* current = head;
    DSListNode<T>* previous = nullptr;

    while (current != nullptr) { //deletes every node
        previous = current;
        current = current->getNext();
        delete previous;
    }
}

template<typename T>
DSLinkList<T>& DSLinkList<T>::operator=(const DSLinkList& arg) { //overloaded assignment operator
    while (!this->isEmpty()) { //remove any nodes currently in the linked list
        this->removeLast();
    }
    if (arg.head == nullptr) { //if the LinkList is empty
        head = nullptr;
        tail = nullptr;
    } else {
        head = new DSListNode<T>;
        head->setData(arg.head->getData()); //create and set the head node

        DSListNode<T>* argCurrent = arg.head;
        if (argCurrent->getNext() == nullptr) { //if the Linked List has only 1 element
            tail = head; //set tail to head
        } else { //if the Linked List has more than 1 element
            while (argCurrent->getNext() != nullptr) { //create and add nodes to the Linked List (with the other Linked List's data)
                argCurrent = argCurrent->getNext();
                this->add(argCurrent->getData());
            }
        }
    }
    return *this; //return the Linked List
}

template<typename T>
void DSLinkList<T>::add(T data) { //adds an element to the Linked List
    DSListNode<T>* current = head; //temporary pointer to iterate over the list (different from curr)

    if (current == nullptr) { //if the Linked List is empty
        DSListNode<T>* newNode = new DSListNode<T>(data); //create a new node with the given data
        newNode->setNext(nullptr); //set next to nullptr
        newNode->setPrevious(nullptr); //set previous to nullptr
        head = newNode; //set head to the new node
        tail = newNode; //set tail to the new node
        curr = head; //initialize curr to head
    } else {
        while (current->getNext() != nullptr) { //iterate to the end of the list
            current = current->getNext();
        }

        DSListNode<T>* newNode = new DSListNode<T>; //create a new node
        newNode->setData(data); //set the node's data to the given data
        newNode->setNext(nullptr); //set next to nullptr
        newNode->setPrevious(current); //set previous to current (which is at the end of the list)

        tail = newNode; //set tail to the new node
        current->setNext(newNode); //set current's next to the new node
    }
}

template<typename T>
void DSLinkList<T>::removeLast() { //removes the last element in the Linked List
    DSListNode<T>* current = head; //temporary pointer to iterate over the list (different from curr)
    DSListNode<T>* previous; //temporary pointer to iterate over the list

    if (current == nullptr) { //if the list is empty
        throw std::out_of_range("The list is empty");
    } else {
        if (current->getNext() == nullptr) { //if only 1 element is in the list
            delete current; //delete the element
            head = nullptr; //set head to nullptr
            tail = nullptr; //set tail to nullptr
        } else { //if there are multiple elements in the list
            while (current->getNext() != nullptr) { //iterate to the end of the list
                previous = current;
                current = current->getNext();
            }
            delete current; //delete current (which is the last element in the list)
            previous->setNext(nullptr); //set previous's next to nullptr
            tail = previous; //set tail to previous
        }
    }
}

template<typename T>
T DSLinkList<T>::getLastData() { //returns the data of the last element in the Linked List
    if (tail != nullptr)
        return tail->getData(); //return the last node's data
    else //if the list is empty
        throw std::out_of_range("The list is empty");
}

template<typename T>
bool DSLinkList<T>::isEmpty() { //returns true if the list is empty, returns false if there is at least 1 element in the list
    if (head == nullptr)
        return true;
    else
        return false;
}

template<typename T>
void DSLinkList<T>::setCurrHead() { //sets curr to head
    curr = head;
}

template<typename T>
void DSLinkList<T>::advanceCurr() { //advances curr by 1 node
    curr = curr->getNext();
}

template<typename T>
void DSLinkList<T>::fallBackCurr() { //decrements curr by 1 node
    curr = curr->getPrevious();
}

template<typename T>
T& DSLinkList<T>::getCurrValue() { //get the node's data that curr points to
     return curr->getData();
}

template<typename T>
bool DSLinkList<T>::hasNext() { //return true if the node curr points to has another node after it, return false if the node curr points to is the last element in the list
    return curr->getNext() != nullptr;
}

template<typename T>
bool DSLinkList<T>::currIsNull() { //return true if curr is set to nullptr, return false otherwise
    if (curr == nullptr) {
        return true;
    } else {
        return false;
    }
}

#endif //INC_21F_FLIGHT_PLANNER_DSLINKLIST_H

//
// Created by mikec_g1kgiu8 on 10/19/2021.
//

#ifndef INC_21F_FLIGHT_PLANNER_DSSTACK_H
#define INC_21F_FLIGHT_PLANNER_DSSTACK_H

#include "DSLinkList.h"

template <typename T>
class DSStack {
    private:
        //Private Variable
        DSLinkList<T> data;

    public:
        //Functions
        void push(const T);
        T pop();
        T peek();
        bool isEmpty();

};

template<typename T>
void DSStack<T>::push(const T arg) { //adds an element to the top of the stack
    data.add(arg);
}

template<typename T>
T DSStack<T>::pop() { //removes the top element from the stack, and returns its value
    T temp = data.getLastData();
    data.removeLast();
    return temp;
}

template<typename T>
T DSStack<T>::peek() { //return the value of the top element in the stack
    return data.getLastData();
}

template<typename T>
bool DSStack<T>::isEmpty() { //return true if the stack is empty, return false if the stack has at least 1 element in it
    return data.isEmpty();
}

#endif //INC_21F_FLIGHT_PLANNER_DSSTACK_H

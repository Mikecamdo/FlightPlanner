//
// Created by mikec_g1kgiu8 on 10/19/2021.
//

#ifndef INC_21F_FLIGHT_PLANNER_DSLISTNODE_H
#define INC_21F_FLIGHT_PLANNER_DSLISTNODE_H

template <typename T>
class DSListNode {
    private:
        //Pointers To Other Nodes
        DSListNode* next;
        DSListNode* previous;

        //Private Variable
        T data;

    public:
        //Constructors
        DSListNode();
        DSListNode(T);

        //Functions
        void setData(T);
        T& getData();
        void setNext(DSListNode*);
        DSListNode* getNext();
        void setPrevious(DSListNode*);
        DSListNode* getPrevious();
};

template<typename T>
DSListNode<T>::DSListNode() {
    next = nullptr;
    previous = nullptr;
}

template<typename T>
DSListNode<T>::DSListNode(T arg) {
    data = arg;
    next = nullptr;
    previous = nullptr;
}

template<typename T>
void DSListNode<T>::setData(T value) { //sets the data to the value passed to it
    data = value;
}

template<typename T>
T& DSListNode<T>::getData() { //returns the data of the node
    return data;
}

template<typename T>
void DSListNode<T>::setNext(DSListNode* arg) { //sets the next pointer to the node passed to it
    next = arg;
}

template <typename T>
DSListNode<T>* DSListNode<T>::getNext() { //returns the pointer to the next node
    return next;
}

template<typename T>
void DSListNode<T>::setPrevious(DSListNode* arg) { //sets the previous pointer to the node passed to it
    previous = arg;
}

template<typename T>
DSListNode<T>* DSListNode<T>::getPrevious() { //returns the pointer to the previous node
    return previous;
}


#endif //INC_21F_FLIGHT_PLANNER_DSLISTNODE_H

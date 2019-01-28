#ifndef LINKEDLIST_HPP
#define	LINKEDLIST_HPP

#include <iostream>
#include "Node.hpp"

using namespace std;

/*....DO NOT EDIT BELOW....*/
template <class T>
class LinkedList {
private:
    Node<T>* head; 
    int length;  
public:

    LinkedList();
    LinkedList(const LinkedList<T>& ll);
    LinkedList<T>& operator=(const LinkedList<T>& ll);
    ~LinkedList();


    Node<T>* getHead() const;
    Node<T>* first() const;
    Node<T>* findPrev(const T& data) const;
    Node<T>* findNode(const T& data) const;
    void insertNode(Node<T>* prev, const T& data); 
    void deleteNode(Node<T>* prevNode);
    void clear();
    size_t getLength() const;
    void print() const;
    void swap(int index1, int index2);
};

template <class T>
void LinkedList<T>::print() const {
    const Node<T>* node = first();
    while (node) {
        std::cout << node->getData();
        node = node->getNext();
    }
    cout << std::endl;
}

/*....DO NOT EDIT ABOVE....*/



/* TO-DO: method implementations below */

template <class T>
LinkedList<T>::LinkedList() {
    head = new Node<T>;
    head->setNext(NULL);
    length = 0;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& ll) {
    Node<T> *iterator, *current, *previous;
    iterator = ll.first();
    head = new Node<T>;
    if(iterator){
        current = new Node<T>;
        *(current->getDataPtr()) = iterator->getData();
        head->setNext(current);
        previous = current;
        iterator = iterator->getNext();
    }
    else return;
    while(iterator){
        current = new Node<T>;
        *(current->getDataPtr()) = iterator->getData();
        previous->setNext(current);
        previous = current;
        iterator = iterator->getNext();
    }
    previous->setNext(NULL);
    length = ll.getLength();
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& ll){
    Node<T> *iterator, *current, *previous;
    clear();
    iterator = ll.first();
    if(iterator){
        current = new Node<T>;
        *(current->getDataPtr()) = iterator->getData();
        head->setNext(current);
        previous = current;
        iterator = iterator->getNext();
    }
    else return *this;
    while(iterator){
        current = new Node<T>;
        *(current->getDataPtr()) = iterator->getData();
        previous->setNext(current);
        previous = current;
        iterator = iterator->getNext();
    }
    previous->setNext(NULL);
    length = ll.getLength();
    return *this;
}

template <class T>
LinkedList<T>::~LinkedList(){
    clear();
    delete head;
}

template <class T>
Node<T>* LinkedList<T>::getHead() const{
    return head;
}

template <class T>
Node<T>* LinkedList<T>::first() const{
    return head->getNext();
}

template <class T>
Node<T>* LinkedList<T>::findPrev(const T& data) const{
    Node<T> *iterator;
    iterator = head;
    while(iterator){
        if (iterator->getNext()->getData() == data) return iterator;
        iterator = iterator->getNext();
    }
    return NULL;
}

template <class T>
Node<T>* LinkedList<T>::findNode(const T& data) const{
    Node<T> *iterator;
    iterator = first();
    while(iterator){
        if (iterator->getData() == data) return iterator;
        iterator = iterator->getNext();
    }
    return NULL;
}

template <class T>
void LinkedList<T>::insertNode(Node<T>* prev, const T& data){
    Node<T> *newNode;
    if (prev == NULL) return;
    newNode = new Node<T>;
    *(newNode->getDataPtr()) = data;
    newNode->setNext(prev->getNext());
    prev->setNext(newNode);
    length++;
    return;
}

template <class T>
void LinkedList<T>::deleteNode(Node<T>* prevNode){
    Node<T> *toDelete;
    if (prevNode == NULL) return;
    toDelete = prevNode->getNext();
    prevNode->setNext(prevNode->getNext()->getNext());
    delete toDelete;
    length--;
    return;
}

template <class T>
void LinkedList<T>::clear(){
    while(first()){
        deleteNode(head);
    }
}

template <class T>
size_t LinkedList<T>::getLength() const{
    return length;
}

template <class T>
void LinkedList<T>::swap(int index1, int index2){
    Node<T> *node1, *node2, *iterator = first();
    T temp;
    int i;
    for (i=0; (i!=index1) && (i!=index2) && (iterator->getNext()); i++){
    iterator = iterator->getNext();
    }
    if (i==index1) node1 = iterator;
    else if (i==index2) node2 = iterator;
    else return;
    for (i++, iterator = iterator->getNext(); (i!=index1) && (i!=index2) && (iterator->getNext()); i++){
    iterator = iterator->getNext();
    }
    if (i==index1) node1 = iterator;
    else if (i==index2) node2 = iterator;
    else return;
    temp = *(node1->getDataPtr());
    *(node1->getDataPtr()) = *(node2->getDataPtr());
    *(node2->getDataPtr()) = temp;
}

/* end of your implementations*/
#endif	



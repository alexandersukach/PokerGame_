#include "DoublyLinkedList.h"

template <class T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

template <class T>
Node<T>* DoublyLinkedList<T>::getHead() const {
    return head;
}

template <class T>
void DoublyLinkedList<T>::pushBack(const T& data) {
    Node<T>* newNode = new Node<T>(data);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

template <class T>
void DoublyLinkedList<T>::pushFront(const T& data) {
    Node<T>* newNode = new Node<T>(data);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}

template <class T>
void DoublyLinkedList<T>::popBack() {
    if (tail == nullptr) {
        return; // empty list
    }
    Node<T>* temp = tail;
    tail = tail->prev;
    if (tail == nullptr) {
        head = nullptr;
    } else {
        tail->next = nullptr;
    }
    delete temp;
}

template <class T>
void DoublyLinkedList<T>::popFront() {
    if (head == nullptr) {
        return; // empty list
    }
    Node<T>* temp = head;
    head = head->next;
    if (head == nullptr) {
        tail = nullptr;
    } else {
        head->prev = nullptr;
    }
    delete temp;
}

template <class T>
void DoublyLinkedList<T>::clear() {
    while (head) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }
    head = tail = nullptr;
}

template <class T>
bool DoublyLinkedList<T>::isEmpty() {
    return head == nullptr && tail == nullptr;
}

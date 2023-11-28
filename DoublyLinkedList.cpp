/*
 *  Implementation of the DoublyLinkedList.cpp class
 */

#include "DoublyLinkedList.h"
#include "Card.h"

template <class T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

// getHead() returns head node of DLL; if empty, nullptr returned
template <class T> Node<T> *DoublyLinkedList<T>::getHead() const {
  return head;
}

// pushBack() creates new node containing data and adds to end of list
template <class T> void DoublyLinkedList<T>::pushBack(const T &data) {
  Node<T> *newNode = new Node<T>(data);
  if (head == nullptr) {
    head = tail = newNode;
  } else {
    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
  }
}
// pushFront() creates new node containing data and adds to beginning of list
template <class T> void DoublyLinkedList<T>::pushFront(const T &data) {
  Node<T> *newNode = new Node<T>(data);
  if (head == nullptr) {
    head = tail = newNode;
  } else {
    newNode->next = head;
    head->prev = newNode;
    head = newNode;
  }
}

// popBack() removes the last element of the list; if empty, do nothing

template <class T> void DoublyLinkedList<T>::popBack() {
  if (tail == nullptr) {
    return; // empty list
  }
  Node<T> *temp = tail;
  tail = tail->prev;
  if (tail == nullptr) {
    head = nullptr;
  } else {
    tail->next = nullptr;
  }
  delete temp;
}

// popFront() removes the first element of the list; if empty, do nothing
template <class T> void DoublyLinkedList<T>::popFront() {
  if (head == nullptr) {
    return; // empty list
  }
  Node<T> *temp = head;
  head = head->next;
  if (head == nullptr) {
    tail = nullptr;
  } else {
    head->prev = nullptr;
  }
  delete temp;
}

// clear() removes all elements from the list; deletes each node to free memory
template <class T> void DoublyLinkedList<T>::clear() {
  while (head) {
    Node<T> *temp = head;
    head = head->next;
    delete temp;
  }
  head = tail = nullptr;
}

// isEmpty() returns true if list is empty
template <class T> bool DoublyLinkedList<T>::isEmpty() const {
  return head == nullptr;
}

// Explicit instantiation of the template for the Card class
template class DoublyLinkedList<Card>;

/*
 *  Declaration of the DoublyLinkedList class
 */
#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

template <class T> struct Node { // ~cardNode~
  T data;                        // card
  Node *next;
  Node *prev;

  Node(const T &data) : data(data), next(nullptr), prev(nullptr) {}
};

template <class T> class DoublyLinkedList {
private:
public:
  Node<T> *head;
  Node<T> *tail;
  DoublyLinkedList();
  //~DoublyLinkedList();
  Node<T> *getHead() const;
  void pushBack(const T &data);
  void pushFront(const T &data);
  void popBack();
  void popFront();
  void clear();
  bool isEmpty() const;
};

#endif // DOUBLYLINKEDLIST_H

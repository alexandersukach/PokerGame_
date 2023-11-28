/*
 *  Declaration of the DoublyLinkedList class
 */
#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

template <class T> struct Node { // Can be thought of as a ~cardNode~
  T data;                        // card
  Node *next;
  Node *prev;

  Node(const T &data) : data(data), next(nullptr), prev(nullptr) {}
};

template <class T> class DoublyLinkedList {
private:
public:
  Node<T> *head; // Pointer to first node in list
  Node<T> *tail; // Point to last node in list
  DoublyLinkedList();
  void pushBack(const T &data);
  void pushFront(const T &data);
  void popBack();
  void popFront();
  void clear();
  bool isEmpty() const;

  //~DoublyLinkedList();
};

#endif // DOUBLYLINKEDLIST_H

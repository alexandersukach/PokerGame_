#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

template <class T>
struct Node {
    T data;
    Node* next;
    Node* prev;

    Node(const T& data) : data(data), next(nullptr), prev(nullptr) {}
};

template <class T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    DoublyLinkedList();
    //~DoublyLinkedList();
    Node<T>* getHead() const;
    void pushBack(const T& data);
    void pushFront(const T& data);
    void popBack();
    void popFront();
    void clear();
    bool isEmpty();
};

#endif // DOUBLYLINKEDLIST_H

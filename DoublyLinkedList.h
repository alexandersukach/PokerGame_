#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

template <class T>
struct ListNode {
    T data;
    ListNode* next;
    ListNode* prev;

    ListNode(const T& data) : data(data), next(nullptr), prev(nullptr) {}
};

template <class T>
class DoublyLinkedList {
private:
    ListNode<T>* head;
    ListNode<T>* tail;

public:
    DoublyLinkedList();
    ListNode<T>* getHead() const;
    void pushBack(const T& data);
    void pushFront(const T& data);
    void popBack();
    void popFront();
    void clear();
    bool isEmpty();
};

#endif

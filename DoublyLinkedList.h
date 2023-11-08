#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include "CardNode.h"

class DoublyLinkedList {
    private:
        CardNode* head;
        CardNode* tail;

    public:
        DoublyLinkedList();
        //~DoublyLinkedList();
        CardNode* getHead() const;
        void pushBack(const Card& card);
        void pushFront(const Card& card);
        void popBack();
        void popFront();
        void clear();
        bool isEmpty();
};

#endif // DOUBLYELINKEDLIST_H

#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H


struct CardNode {
    Card card;
    CardNode* next;
    CardNode* prev;
    
    CardNode(const Card& c) : card(c), next(nullptr), prev(nullptr) {}
};

class DoublyLinkedList {
    private:
        CardNode* head;
        CardNode* tail;
    
    public:
        DoublyLinkedList();
        void pushBack(const Card& card);
        void pushFront(const Card& card);
        void popBack(const Card& card);
        void popFront(const Card& card);
        void clear();
        bool isEmpty();
};



#endif
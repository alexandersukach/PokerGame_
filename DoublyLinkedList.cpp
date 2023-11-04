#include "DoublyLinkedList.h"

DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr);

void DoublyLinkedList::pushBack(const Card& card) {
    CardNode* newNode = new CareNode(card);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

void DoublyLinkedList::pushFront(const Card& card) {
    CardNode* newNode = new CardNode(card);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}

void DoublyLinkedList::popBack(const Card& card) {
    if (tail == nullptr) {
        return; // empty list
    }
    CardNode* temp = tail;
    tail = tail->prev;
    if (tail == nullptr) {
        head = nullptr;
    } else {
        tail->next = nullptr;
    }
    delete temp;
}
// Adding something to see if this syncs w github
void DoublyLinkedList::popFront(const Card& card) {
    if (head == nullptr) {
        return; // empty list
    }
    CardNode* temp = head;
    head = head->next;
    if (head == nullptr) {
        tail = nullptr;
    } else {
        head->prev = nullptr;
    }
    delete temp;
}


void DoublyLinkedList::clear() {
    while (head) {
        CardNode* temp = head;
        head = head->next;
        delete temp;
    }
    head == tail == nullptr;
}

bool DoublyLinkedList::isEmpty() {
    return head == nullptr && tail == nullptr;
}





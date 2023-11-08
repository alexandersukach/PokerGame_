#include "DoublyLinkedList.h"
#include "CardNode.h"


DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

CardNode* DoublyLinkedList::getHead() const {
    return head;
}

void DoublyLinkedList::pushBack(const Card& card) {
    CardNode* newNode = new CardNode(card);
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
    if(head == nullptr) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}

void DoublyLinkedList::popBack() {
    delete tail;
    tail = tail->prev;
    tail->next = nullptr;
}

void DoublyLinkedList::popFront() {
    delete head;
    head = head->next;
    head->prev = nullptr;
}

void DoublyLinkedList::clear() {
    while (head) {
        CardNode* temp = head;
        head = head->next;
        delete temp;
    }
    head = tail = nullptr;
}

bool DoublyLinkedList::isEmpty() {
    return head == nullptr && tail == nullptr;
}

/*
~/Desktop/PokerGame_> g++ -std=c++17 DoublyLinkedList.cpp
Undefined symbols for architecture x86_64:
  "_main", referenced from:
     implicit entry/start for main executable
ld: symbol(s) not found for architecture x86_64
clang: error: linker command failed with exit code 1 (use -v to see invocation)*/
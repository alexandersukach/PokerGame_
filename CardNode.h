#ifndef CARDNODE_H
#define CARDNODE_H
#include "Card.h"

struct CardNode {
    Card card; 
    CardNode* next;
    CardNode* prev;

    CardNode(const Card& value) : value(value), next(nullptr), prev(nullptr) {}
};

#endif // CARDNODE_H

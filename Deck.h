#ifndef DECK_H
#define DECK_H

#include "DoublyLinkedList.h" 
#include "CardNode.h"

class Deck {
private:
    DoublyLinkedList<CardNode> deck; 

    void initializeDeck();
    void shuffleDeck();
    void cutDeck();

public:
    Deck();
    Card dealCard();
    void burnCard();
};

#endif // DECK_H
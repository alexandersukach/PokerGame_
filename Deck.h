#ifndef DECK_H
#define DECK_H

#include "DoublyLinkedList.h"
#include "Card.h"

class Deck {
    private:
        DoublyLinkedList<Card> deck;
    
        void InitializeDeck();
        void shuffleDeck();
        void cutDeck();

    public:
        Deck();
        Card dealCard();
        // bool isEmpty();
        void burnCard();
};



#endif // DECK_H
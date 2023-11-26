#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include "DoublyLinkedList.h"
#include <iostream>

class Deck {
private:
  DoublyLinkedList<Card> deck;

  void initializeDeck();
  void shuffleDeck();
  void cutDeck();

public:
  void print() {
    for (auto x{deck.head}; x != nullptr; x = x->next)
      std::cout << x->data.getRank() << ' ' << x->data.getSuit() << std::endl;
  }
  Deck();
  Card dealCard();
  void burnCard();
};

#endif // DECK_H
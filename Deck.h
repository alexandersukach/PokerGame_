/*
 *  Declaration of the Deck class
 */
#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include "DoublyLinkedList.h"
#include <iostream>

using namespace std;

// Deck class represents a standard deck of playing cards
class Deck {
private:
  DoublyLinkedList<Card> deck; // Deck represented as a doublylinkedlist
  void initializeDeck();       // Ceck initialized with 52 playing cards
  void shuffleDeck();          // Ceck shuffed using a random seed
  void cutDeck(); // Deck is cut (top and bottom halves are swapped)
public:
  Deck();
  Card dealCard(); // Deal card from top of deck
  void burnCard(); // Remove top card from deck

  void print() const {
    for (auto x = deck.head; x; x = x->next)
      cout << x->data.getRank() << ' ' << x->data.getSuit() << '\n';
  }
};

#endif // DECK_H
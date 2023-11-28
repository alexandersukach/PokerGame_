/*
 *  Implementation of the Deck class
 */
#include "Deck.h"
#include "Card.h"
#include "DoublyLinkedList.h"
#include <algorithm>
#include <random> // for mt19937
#include <vector>
using namespace std;

Deck::Deck() {
  initializeDeck(); // Fill standard deck of 52 playing cards
  shuffleDeck();    // Shuffle deck using random seed
  cutDeck();        // Swap the deck's top and bottom halves
} // Deck is now ready

// An unshuffled dick is created/organized 2-A for each suit
void Deck::initializeDeck() {
  for (int suit = Card::HEARTS; suit <= Card::SPADES; suit++) {
    for (int rank = Card::TWO; rank <= Card::ACE; rank++) {
      deck.pushBack(
          Card{static_cast<Card::Rank>(rank), static_cast<Card::Suit>(suit)});
    }
  }
}

void Deck::shuffleDeck() {
  // Temporary vector to store cards during shuffling process
  vector<Card> tempDeck;

  while (!deck.isEmpty()) {
    Node<Card> *head = deck.head;
    if (head != nullptr) {
      tempDeck.push_back(head->data);
      deck.popFront();
    } else {
      // Ensure deck is not empty
      throw runtime_error("No deck to shuffle.");
    }
  }
  // It is recommended to shuffle a deck 7 times
  for (int i = 0; i < 7; i++) {
    // Mersenne Twister randNum generator for thorough shuffling
    shuffle(tempDeck.begin(), tempDeck.end(), mt19937(random_device()()));
  }
  // Move shuffled cards to original deck
  for (const auto &card : tempDeck) {
    deck.pushBack(card);
  }
}

void Deck::cutDeck() {
  if (deck.isEmpty()) {
    throw runtime_error("No deck to cut.");
  }

  // Find the midpoint of the deck
  Node<Card> *midpoint = deck.head;
  Node<Card> *current = deck.head;
  while (current != nullptr && current->next != nullptr) {
    midpoint = midpoint->next;
    current = current->next->next;
  }
  // Separate the deck into two halves
  DoublyLinkedList<Card> bottomHalf;
  bottomHalf.head = midpoint->next;
  midpoint->next->prev = nullptr;
  midpoint->next = nullptr;

  // Combine the two halves back together
  deck.tail->next = deck.head;
  deck.head->prev = deck.tail;

  // Update the head and tail pointers
  deck.head = bottomHalf.head;
  deck.tail = bottomHalf.head->prev;
}

void Deck::burnCard() { deck.popFront(); }

// The top card of deck is deal to player
Card Deck::dealCard() {
  if (deck.isEmpty()) {
    // Ensure deck is not empty
    throw runtime_error("Cannot deal card. Deck is empty.");
  }
  Card dealtCard = deck.head->data;
  deck.popFront();
  return dealtCard;
}

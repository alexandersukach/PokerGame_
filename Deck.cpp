/*
Deck Class:
  - represents a standard deck (52 cards)
  - for each game round, a new deck is created, shuffled, and cut
*/
#include "Deck.h"
#include "DoublyLinkedList.h"
#include "Card.h"
#include <vector>
#include <algorithm>
#include <random> // for mt19937
using namespace std;

Deck::Deck() {
    initializeDeck(); // Fill standard deck of 52 playing cards
    shuffleDeck(); // Shuffle deck using random seed
    cutDeck(); // Swap the deck's top and bottom halves
}

void Deck::initializeDeck() {
    for (int suit = Card::HEARTS; suit <= Card::SPADES; suit++) {
        for (int rank = Card::TWO; rank <= Card::ACE; rank++) {
            // Map a numeric rank to each actual rank
            Card::Rank actualRank;
            if (rank == Card::JACK) {
                actualRank = Card::Rank(11);
            } else if (rank == Card::QUEEN) {
                actualRank = Card::Rank(12);
            } else if (rank == Card::KING) { 
                actualRank = Card::Rank(13); 
            } else if (rank == Card::ACE) {
                actualRank = Card::Rank(14); 
            } else {
                actualRank = Card::Rank(rank);
            }
            // Card added to deck 
            deck.pushBack(Card(actualRank, static_cast<Card::Suit>(suit)));
        }
    }
}

void Deck::shuffleDeck() {
    // Temporary vector to store cards for shuffling
    vector<Card> tempDeck;

    while (!deck.isEmpty()) {
        Node<Card>* head = deck.getHead();
        if (head!= nullptr) {
            tempDeck.push_back(head->data);
            deck.popFront();
        } else {
            throw runtime_error("No deck to shuffle.");
        }
    }
    // Recommended to shuffle a deck 7 times
    for (int i = 0; i < 7; i++) {
        // Mersenne Twister randNum generator for thorough shuffling 
        shuffle(tempDeck.begin(), tempDeck.end(), mt19937(random_device()()));
    }
    // Move shuffled cards to original deck
    for (const auto& card : tempDeck) {
        deck.pushBack(card);
    }
}

void Deck::cutDeck() {
    DoublyLinkedList<Card> bottomHalf;
    DoublyLinkedList<Card> topHalf;
    int cutpoint = 26;

    // Move top half of deck into one list
   for (int i = 0; i < cutpoint; i++) {
        Node<Card>* head = deck.getHead();
        if (head != nullptr) {
            topHalf.pushBack(head->data);
            deck.popFront();
        } else {
            throw runtime_error("No deck to cut.");
        }
    }
    // Move bottom half of deck into one list
    while (!deck.isEmpty()) {
        Node<Card>* head = deck.getHead();
        if (head != nullptr) {
            bottomHalf.pushBack(head->data);
            deck.popFront();
        } else {
            throw runtime_error("No deck to cut.");
        }
    }
    // Merge the two lists back together
    deck.clear();
    
    // Add bottom half to list (new top half)
    while (!bottomHalf.isEmpty()) {
        Node<Card>* bottomHead = bottomHalf.getHead();
        if (bottomHead != nullptr) {
            deck.pushBack(bottomHead->data);
            bottomHalf.popFront();
        } else {
            throw runtime_error("No lower half of deck.");
        }
    }
    // Add top half to list (new bottom half)
    while (!topHalf.isEmpty()) {
        Node<Card>* topHead = topHalf.getHead();
        if (topHead != nullptr) {
            deck.pushBack(topHead->data);
            topHalf.popFront();
        } else {
            throw runtime_error("No upper half of deck.");
        }
    }
}

void Deck::burnCard() {
    deck.popFront();
}

Card Deck::dealCard() {
    if (deck.isEmpty()) {
        throw runtime_error("Cannot deal card. Deck is empty.");
    }

    Card dealtCard = deck.getHead()->data;
    deck.popFront();
    return dealtCard;
}


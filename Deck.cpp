#include "Deck.h"
#include "DoublyLinkedList.h"
#include "Card.h"
#include <vector>
#include <algorithm>
#include <random>

Deck::Deck() {
    initializeDeck();
    shuffleDeck();
    cutDeck();
}

void Deck::initializeDeck() {
    for (int suit = Card::HEARTS; suit <= Card::SPADES; suit++) {
        for (int rank = Card::TWO; rank <= Card::ACE; rank++) {
            Card::Rank actualRank;
            if (rank == Card::JACK) {
                actualRank = Card::Rank(11);
            } else if (rank == Card::QUEEN) {
                actualRank = Card::Rank(12);
            } else if (rank == Card::KING) { // Not sure if the 11 - 14 ranking 
                actualRank = Card::Rank(13); // is most appropriate
            } else if (rank == Card::ACE) {
                actualRank = Card::Rank(14); // or 14 depending on the hand, still haven't figured it out...
            } else {
                actualRank = Card::Rank(rank);
            }

            deck.pushBack(Card(actualRank, static_cast<Card::Suit>(suit)));
        }
    }
}

void Deck::shuffleDeck() {
    DoublyLinkedList<Card> tempDeck;
    while (!deck.isEmpty()) {
        tempDeck.pushBack(deck.getHead()->data);
        deck.popFront();
    }

    std::vector<Card> tempVector;

    while (!tempDeck.isEmpty()) {
        tempVector.push_back(tempDeck.getHead()->data);
        tempDeck.popFront();
    }

    for (int i = 0; i < 7; i++) {
        std::shuffle(tempVector.begin(), tempVector.end(), std::mt19937(std::random_device()()));
    }

    for (const auto& card : tempVector) {
        deck.pushBack(card);
    }
}

void Deck::cutDeck() {
    DoublyLinkedList<Card> bottomHalf;
    DoublyLinkedList<Card> topHalf;
    int cutpoint = 26;

    for (int i = 0; i < cutpoint; i++) {
        topHalf.pushBack(deck.getHead()->data);
        deck.popFront();
    }

    while (!deck.isEmpty()) {
        bottomHalf.pushBack(deck.getHead()->data);
        deck.popFront();
    }

    while (!topHalf.isEmpty()) {
        deck.pushBack(topHalf.getHead()->data);
        topHalf.popFront();
    }

    while (!bottomHalf.isEmpty()) {
        deck.pushBack(bottomHalf.getHead()->data);
        bottomHalf.popFront();
    }
}

void Deck::burnCard() {
    deck.popFront(); // Use popFront() to burn the top card
}

Card Deck::dealCard() {
    Card card = deck.getHead()->data;
    deck.popFront();
    return card;
}


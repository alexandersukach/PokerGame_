#include "Deck.h"
#include "DoublyLinkedList.h" // Include the necessary header for DoublyLinkedList
#include "Card.h" // Include the necessary header for Card
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
            } else if (rank == Card::KING) {
                actualRank = Card::Rank(13);
            } else if (rank == Card::ACE) {
                actualRank = Card::Rank(14); // or 14 depending on the hand
            } else {
                actualRank = Card::Rank(rank);
            }

            deck.pushBack(Card(actualRank, static_cast<Card::Suit>(suit)));
        }
    }
}


void Deck::initializeDeck() {
    for (int suit = Card::HEARTS; suit <= Card::SPADES; suit++) {
        for (int rank = Card::TWO; rank <= Card::ACE; rank++) {
            Card::Rank actualRank;
            if (rank == Card::JACK) {
                actualRank = Card::Rank(11);
            } else if (rank == Card::QUEEN) {
                actualRank = Card::Rank(12);
            } else if (rank == Card::KING) {
                actualRank = Card::Rank(13);
            } else if (rank == Card::ACE) {
                actualRank = Card::Rank(14); // or 14 depending on the hand
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

// Human error would entail approx halfway...should I include a random number generator within a valid range of "halfway" values
        // Linked list to represent deck
        

void Deck::burnCard() {
    deck.popFront(); // Use popFront() to burn the top card
}

Card Deck::dealCard() {
    Card card = deck.getHead()->data;
    deck.popFront(); // Use popFront() to deal the top card
    return card;
}

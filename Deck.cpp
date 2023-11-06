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

void Deck::shuffleDeck() {
    std::vector<Card> tempVector;

    while (!deck.isEmpty()) {
        tempVector.push_back(deck.getHead()->data);
        deck.popFront(); // Use popFront() to remove the card from the linked list
    }

    for (int i = 0; i < 7; i++) {
        std::shuffle(tempVector.begin(), tempVector.end(), std::mt19937(std::random_device()()));
    }

    for (const auto& card : tempVector) {
        deck.pushBack(card);
    }
}

void Deck::cutDeck() {
    // Implement the cutDeck method as you intended
}

void Deck::burnCard() {
    deck.popFront(); // Use popFront() to burn the top card
}

Card Deck::dealCard() {
    Card card = deck.getHead()->data;
    deck.popFront(); // Use popFront() to deal the top card
    return card;
}

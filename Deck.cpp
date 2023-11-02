#include "Deck.h"
#include "DoublyLinkedList.h"
#include <vector>
#include <algorithm>
#include <random>

Deck::Deck() {
    initializeDeck();
    shuffleDeck();
    cutDeck();
}

/*
    void InitializeDeck() {
    for (int suit = Card::HEARTS; suit <= Card::SPADES; suit++) {
        for (int rank = Card::TWO; rank <= Card::ACE; rank++) {
            Rank actualRank;
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

            deck.push(Card(actualRank, static_cast<Card::Suit>(suit)));
        }
    }
}*/

void Deck::ShuffleDeck() {
    std::vector<Card> tempVector;

    while (!deck.isEmpty()) {
        tempVector.push_back(deck.getHead()->card);
        deck.popHead();
    }
    // .begin() and .end() specify the range we would like to shuffle, in this case the entire deck.
    // mt19937 - Mersenne Twister Algorithm; random_device() - random number generator device, seeds engine mt19937
    for(int i = 0; i < 7; i++) {
        std::shuffle(tempVector.begin(), tempVector.end(), stdd::mt19937(std::random_device()())); // single line seed -> immediate val
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
        topHalf.pushBack(deck.getHead()->card);
        deck.popFront();
    }

    while (!deck.isEmpty()) {
        bottomHalf.pushBack(deck.getHead()->card);
        deck.popFront();
    }
    
    for (!bottomHalf.isEmpty()) {
        deck.pushBack(bottomHalf.getHead()->card);
        bottomHalf.popFront();
    }

    while(!topHalf.isEmpty()) {
        deck.pushBack(topHalf.getHead()->card);
        topHalf.popFront();
    }
}

void Deck::burnCard() {
    deck.popFront();
}

Card Deck::dealCard() {
    Card card = deck.getHead()->card;
    deck.popFront();
    return card;
}

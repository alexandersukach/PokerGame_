#include "Hand.h"
#include <algorithm>

bool compareCardsByRank(const Card& a, const Card& b) {
    return a.getRank() < b.getRank();
}

Hand::Hand(const std::vector<Card>& handCards) : cards(handCards) {
    // sortCards();
}

std::vector<Card> sortCards(const std::vector<Card>& unsorted) {
    // Your implementation for sorting the cards
    std::vector<Card> sortedCards = unsorted; // Make a copy of the unsorted cards
    std::sort(sortedCards.begin(), sortedCards.end(), compareCardsByRank); // Use the sorting function you've defined
    return sortedCards;
}

int Hand::calculateScore() const {
    std::vector<Card> sortedCards = sortCards(cards); // Copy cards for sorting
    //sortCards(sortedCards); // Sort the copy

    if (isRoyalFlush(sortedCards)) {
        return 10;
    } else if (isStraightFlush(sortedCards)) {
        return 9;
    } else if (isFourOfAKind(sortedCards)) {
        return 8;
    } else if (isFullHouse(sortedCards)) {
        return 7;
    } else if (isFlush(sortedCards)) {
        return 6;
    } else if (isStraight(sortedCards)) {
        return 5;
    } else if (isThreeOfAKind(sortedCards)) {
        return 4;
    } else if (isTwoPair(sortedCards)) {
        return 3;
    } else if (isOnePair(sortedCards)) {
        return 2;
    } else {
        return 1;
    }
}

bool Hand::isOnePair(const std::vector<Card>& sortedCards) const {
    for (size_t i = 0; i < sortedCards.size() - 1; i++) {
        if (sortedCards[i].getRank() == sortedCards[i + 1].getRank()) {
            return true;
        }
    }
    return false;
}

bool Hand::isTwoPair(const std::vector<Card>& sortedCards) const {
    int numPairs = 0;
    for (size_t i = 0; i < sortedCards.size() - 1; i++) {
        if (sortedCards[i].getRank() == sortedCards[i + 1].getRank()) {
            numPairs++;
            i++;
        }
    }
    return numPairs == 2;
}

bool Hand::isThreeOfAKind(const std::vector<Card>& sortedCards) const {
    for (size_t i = 0; i < sortedCards.size() - 2; i++) {
        if (sortedCards[i].getRank() == sortedCards[i + 1].getRank() &&
            sortedCards[i].getRank() == sortedCards[i + 2].getRank()) {
            return true;
        }
    }
    return false;
}

bool Hand::isFourOfAKind(const std::vector<Card>& sortedCards) const {
    for (size_t i = 0; i < sortedCards.size() - 3; i++) {
        if (sortedCards[i].getRank() == sortedCards[i + 1].getRank() &&
            sortedCards[i].getRank() == sortedCards[i + 2].getRank() &&
            sortedCards[i].getRank() == sortedCards[i + 3].getRank()) {
            return true;
        }
    }
    return false;
}

bool Hand::isFlush(const std::vector<Card>& sortedCards) const {
    // Check if all cards have the same suit
    for (size_t i = 1; i < sortedCards.size(); i++) {
        if (sortedCards[i].getSuit() != sortedCards[0].getSuit()) {
            return false;
        }
    }
    return true;
}

bool Hand::isStraight(const std::vector<Card>& sortedCards) const {
    // Check if the ranks form a consecutive sequence
    for (size_t i = 0; i < sortedCards.size() - 1; i++) {
        if (sortedCards[i].getRank() != sortedCards[i + 1].getRank() - 1) {
            return false;
        }
    }
    return true;
}

bool Hand::isFullHouse(const std::vector<Card>& sortedCards) const {
    // A full house consists of three cards of one rank and two cards of another rank
    if (sortedCards[0].getRank() == sortedCards[1].getRank() &&
        sortedCards[3].getRank() == sortedCards[4].getRank() &&
        (sortedCards[2].getRank() == sortedCards[0].getRank() || sortedCards[2].getRank() == sortedCards[3].getRank())) {
        return true;
    }
    return false;
}

bool Hand::isStraightFlush(const std::vector<Card>& sortedCards) const {
    return isStraight(sortedCards) && isFlush(sortedCards);
}

bool Hand::isRoyalFlush(const std::vector<Card>& sortedCards) const {
    // Royal Flush is a special case of a Straight Flush
    if (isStraightFlush(sortedCards) && sortedCards[4].getRank() == Card::ACE) {
        return true;
    }
    return false;
}

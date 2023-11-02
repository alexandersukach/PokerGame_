#include "Hand.h"
#include <algorithm>

bool compareCardsByRank(const Card& a, const Card& b) {
    return a.getRank() < b.getRank();
}

Hand::Hand(const std::vector<Card>& handCards) : cards(handCards) {
    sortCards();
}

void Hand::sortCards() {
    std::sort(cards.begin(), cards.end(), compareCardsByRank);
}

int Hand::calculateScore() const {
    std::vector<Card> sortedCards = sortCards(cards);
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


bool Hand::isOnePair() const {
    for (int i = 0; i < cards.size() - 1; i++) {
        for(int j = i + 1; j < cards.size(); j++) {
            if(cards[i].getRank() == cards[j].getRank) {
                return true;
            }
        }
    }
    return false;
}

bool Hand::isTwoPair() const {
    int numPairs = 0;
    for (int i = 0; i < cards.size() - 1; i++) {
        for (int j = i + 1; j < cards.size(); j++) {
            if(cards[i].getRank() == cards[j].getRank()) {
                numPairs++;
                j++; // Skip 
            }
        }
    }
}
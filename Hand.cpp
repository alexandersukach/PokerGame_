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

int Hand::calculateBestHandScore() const {
        int bestScore = 0;
        // Iterate through all combinations of 5 cards
        for (int i = 0; i < cards.size() - 4; i++) {
            for (int j = i + 1; j < cards.size() - 3; j++) {
                for (int k = j + 1; k < cards.size() - 2; k++) {
                    for (int m = k + 1; m < cards.size() - 1; m++) {
                        for (int n = m + 1; n < cards.size(); n++) {
                            // Create a temporary hand with the selected 5 cards
                            std::vector<Card> tempHand = {cards[i], cards[j], cards[k], cards[m], cards[n]};
                            // Calculate the score for this combination
                            int score = calculateScore(tempHand);
                            // Update the best score if this combination is better
                            if (score > bestScore) {
                                bestScore = score;
                            }
                        }
                    }
                }
            }
        }
        return bestScore;
    }
int Hand::calculateScore(const std::vector<Card>& hand) const {
    std::vector<Card> sortedCards = sortCards(cards); // Copy cards for sorting

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
    for (int i = 0; i < sortedCards.size() - 1; i++) {
        if (sortedCards[i].getRank() == sortedCards[i + 1].getRank()) {
            return true;
        }
    }
    return false;
}

bool Hand::isTwoPair(const std::vector<Card>& sortedCards) const {
    int numPairs = 0;
    for (int i = 0; i < sortedCards.size() - 1; i++) {
        if (sortedCards[i].getRank() == sortedCards[i + 1].getRank()) {
            numPairs++;
            i++;
        }
    }
    return numPairs == 2;
}

bool Hand::isThreeOfAKind(const std::vector<Card>& sortedCards) const {
    for (int i = 0; i < sortedCards.size() - 2; i++) {
        if (sortedCards[i].getRank() == sortedCards[i + 1].getRank() &&
            sortedCards[i].getRank() == sortedCards[i + 2].getRank()) {
            return true;
        }
    }
    return false;
}

bool Hand::isFourOfAKind(const std::vector<Card>& sortedCards) const {
    for (int i = 0; i < sortedCards.size() - 3; i++) {
        if (sortedCards[i].getRank() == sortedCards[i + 1].getRank() &&
            sortedCards[i].getRank() == sortedCards[i + 2].getRank() &&
            sortedCards[i].getRank() == sortedCards[i + 3].getRank()) {
            return true;
        }
    }
    return false;
}

bool Hand::isFlush(const std::vector<Card>& sortedCards) const {
    for (int i = 0; i < sortedCards.size() - 1; i++) {
        if (sortedCards[i].getSuit() != sortedCards[i + 1].getSuit()) {
            return false;
        }
    }
    return true;
}

bool Hand::isStraight(const std::vector<Card>& sortedCards) const {
    // Check if the ranks form a consecutive sequence
    for (int i = 0; i < sortedCards.size() - 1; i++) {
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

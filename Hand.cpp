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
/*
int Hand::calculateBestHandScore() const {
        int bestScore = 0;

        // Iterate through all combinations of 5 cards
        for (size_t i = 0; i < cards.size() - 4; i++) {
            for (size_t j = i + 1; j < cards.size() - 3; j++) {
                for (size_t k = j + 1; k < cards.size() - 2; k++) {
                    for (size_t m = k + 1; m < cards.size() - 1; m++) {
                        for (size_t n = m + 1; n < cards.size(); n++) {
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
    */
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
    bool oldPair = false; // Pair already seen so we don't repeat pair count
    for (int i = 0; i < cards.size() - 1; i++) {
        for (int j = i + 1; j < cards.size(); j++) {
            if(cards[i].getRank() == cards[j].getRank()) {
                if (!oldPair) {
                    numPairs++;
                    oldPair = true;
                } else {
                    oldPair = false;
                }
            }
        }
    }
    return numPairs == 2;
}

bool Hand::isThreeOfAKind() const {
    for (int i = 0; i < cards.size() - 2; i++) {
        int numMatches = 0;
        for (int j = i + 1; j < cards.size(); j++) {
            if(cards[i].getRank() == cards[j].getRank()) {
                numMatches++;
            }
        }
        if(numMatches == 2) {
            return true;
        }
    }
    return false
}

// bool Hand::isStraight() const {}
// bool Hand::isFlush() const {}
// bool Hand::isFourOfAKind() const{}
/*
bool Hand::isStraightFlush() {
    return isStraight() && isFlush();
}

*/
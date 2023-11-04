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

// if the hand the score's being evaluated for is 5 cards,
// should i be swapping based on 5 for all the cards.size()

// Remember to keep in mind, the cards are sorted...
// Drawing 5 cards of 7

//isOnePair() - all we need is one match
// I want to try kinda moving up the chain 

bool Hand::isOnePair() const {
    int j = 0;
    int k = 1;
    while (j < cards.size() && k < cards.size()) {
            for (int i = 0; i < cards.size() - 1; i++) {
        if(cards[j].getRank() == cards[k].getRank()) {
            return true;
        } else if(j > k) {
            k += 2;
        } else {
            j += 2;
        }
    }
    }
}

//isTwoPair() - we need two matches...say cards 1 and 2 are a pair,
// we need to jump and start check at j+1 for i and j+2 for j? 
// include counterofpairs and return whether equal 2;
// Going to approach like above...

bool Hand::isTwoPair() const {
    int j = 0;
    int k = 1;
    int numPairs = 0;
    while (j < cards.size() && k < cards.size()) {
            for (int i = 0; i < cards.size(); i++) {
        if(numPairs == 2) {
            return true;
        }
        if(cards[j].getRank() == cards[k].getRank()) {
            numPairs++;
            j += 2;
            k += 2;
        } else (if j > k) {
            k += 2;
        } else {
            j += 2;
        }
    }
    }
}


// only check first three cards to match the consecutive two

// example should i do while i <=2
bool Hand::isThreeOfAKind() const {
    for (int i = 0; i < cards.size() - 2; i++) {
        if (cards[i].getRank() == cards[i+1].getRank() &&
            cards[i+1].getRank() == cards[i+2].getRank()) {
                return true;
            }
    }
    return false;
}

// same logic for 4ofkind?

bool Hand::isFourOfAKind() const {
    for (int i = 0; i < cards.size() - 3; i++) {
        if (cards[i].getRank() == cards[i + 1].getRank() &&
            cards[i + 1].getRank() == cards[i + 2].getRank() &&
            cards[i + 2].getRank() == cards.[i + 3].getRank()) {
                return true;
            }
    }
    return false;
}

bool Hand::isFlush() {
    Card::Suit cardSuit;

    for (int i = 0; i < cards.size(); i++) {
        int numSpades;
        int numClubs;
        int numDiamonds;
        int numHearts;
        cardSuit = cards[i].getSuit();
        if (cardSuit == "SPADES") {
            numSpades++;
        } else if (cardSuit == "CLUBS") {
            numClubs++;
        } else if (cardSuit == "DIAMONDS") {
            numDiamonds++;
        } else {
            numHearts++;
        }
    }
}

bool Hand::isStraight() {
    for (int i = 0; i < cards.size() - 3; i++) {
        if ((cards[i].getRank() == cards[i + 1].getRank() - 1) &&
        (cards[i + 1].getRank() == cards[i + 2].getRank() - 1) &&
        (cards[i + 2].getRank() == cards[i + 3].getRank() - 1)) {
            return true;
        }
    }
}
// bool Hand::isStraight() const {}
// bool Hand::isFlush() const {}
// bool Hand:: isFullHouse() const { return isOnePair() && isThreeOfAKind() }
// bool Hand::isFourOfAKind() const{}
/*
bool Hand::isStraightFlush() { return isStraight() && isFlush(); }

*/
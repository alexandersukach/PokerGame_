#ifndef HAND_H
#define HAND_H

#include "Card.h"
#include <vector>

class Hand {
    private:
        std::vector<Card> cards;
        std::vector<Card> sortCards(const std::vector<Card>& unsorted) const;

    public:
        Hand(const std::vector<Card>& handCards);
        int calculateBestHandScore() const;
        int calculateScore() const;
        bool isOnePair() const;
        bool isTwoPair() const;
        bool isThreeOfAKind() const;
        bool isStraight() const;
        bool isFlush() const;
        bool isFourOfAKind() const;
        bool isStraightFlush() const;
        bool isRoyalFlush() const;
}




#endif // HAND_H
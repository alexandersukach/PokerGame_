#ifndef HAND_H
#define HAND_H

#include "Card.h"
#include <vector>

class Hand {
    private:
        std::vector<Card> cards;

    public:
    Hand(const std::vector<Card>& handCards);
    static std::vector<Card> sortCards(const std::vector<Card>& unsorted);
    int calculateScore(const std::vector<Card> &sortedCards) const;
    int calculateBestHandScore() const;
    bool isOnePair(const std::vector<Card> &sortedCards) const;
    bool isTwoPair(const std::vector<Card> &sortedCards) const;
    bool isThreeOfAKind(const std::vector<Card> &sortedCards) const;
    bool isStraight(const std::vector<Card> &sortedCards) const;
    bool isFlush(const std::vector<Card> &sortedCards) const;
    bool isFullHouse(const std::vector<Card> &sortedCards) const;
    bool isFourOfAKind(const std::vector<Card> &sortedCards) const;
    bool isStraightFlush(const std::vector<Card> &sortedCards) const;
    bool isRoyalFlush(const std::vector<Card> &sortedCards) const;
};

#endif // HAND_H

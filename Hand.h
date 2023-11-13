#ifndef HAND_H
#define HAND_H

#include "Card.h"
#include <vector>
using namespace std;

class Hand {
    private:
        vector<Card> cards;

    public:
    Hand(const vector<Card>& handCards);
    static vector<Card> sortCards(const vector<Card>& unsorted);
    int calculateScore(const vector<Card> &sortedCards) const;
    int calculateBestHandScore() const;
    bool isOnePair(const vector<Card> &sortedCards) const;
    bool isTwoPair(const vector<Card> &sortedCards) const;
    bool isThreeOfAKind(const vector<Card> &sortedCards) const;
    bool isStraight(const vector<Card> &sortedCards) const;
    bool isFlush(const vector<Card> &sortedCards) const;
    bool isFullHouse(const vector<Card> &sortedCards) const;
    bool isFourOfAKind(const vector<Card> &sortedCards) const;
    bool isStraightFlush(const vector<Card> &sortedCards) const;
    bool isRoyalFlush(const vector<Card> &sortedCards) const;
};

#endif // HAND_H

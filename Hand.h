/*
 *  Declaration of the Hand class
 */
#ifndef HAND_H
#define HAND_H

#include "Card.h"
#include <vector>
using namespace std;

// Hand class represents 5 card handle used to determine winner
class Hand {
private:
  vector<Card> cards; // Vector to store cards in hand

public:
  Hand(const vector<Card> &handCards);
  // Cards in hand are sorted for score calculation
  static vector<Card> sortCards(const vector<Card> &unsorted);

  int calculateScore(const vector<Card> &sortedCards) const;
  int calculateBestHandScore() const;

  // Score definitions for each hand
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

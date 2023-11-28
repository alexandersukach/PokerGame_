/*
 *  Implementation of the Hand class
 */

#include "Hand.h"
#include <algorithm>

bool compareCardsByRank(const Card &a, const Card &b) {
  return a.getRank() <
         b.getRank(); // returns true if a's rank is less than b's rank
}

Hand::Hand(const vector<Card> &handCards) : cards(sortCards(handCards)) {
  // sortCards();
}

// Sorts vector of cards by rank
vector<Card> Hand::sortCards(const vector<Card> &unsorted) {
  vector<Card> sortedCards = unsorted; // Make a copy of the unsorted cards
  sort(sortedCards.begin(), sortedCards.end(), compareCardsByRank); //
  return sortedCards;
}

int Hand::calculateBestHandScore() const {
  int bestScore = 0;
  // Iterate through all combinations of 5 cards
  for (int i = 0; i < 3; i++) { // No need to check after fourth card
    for (int j = i + 1; j < 4; j++) {
      for (int k = j + 1; k < 5; k++) {
        for (int m = k + 1; m < 6; m++) {
          for (int n = m + 1; n < 7; n++) {
            vector<Card> tempHand = {cards[i], cards[j], cards[k], cards[m],
                                     cards[n]};
            // Calculate the score for each possible 5 card combination
            int score = calculateScore(tempHand);
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

int Hand::calculateScore(const vector<Card> &hand) const {
  vector<Card> sortedCards = sortCards(hand);
  // Calculate score of sorted hand
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

// Hand contains a pair of cards of the same rank; suit neglected
bool Hand::isOnePair(const vector<Card> &sortedCards) const {
  for (int i = 0; i < sortedCards.size() - 1; i++) {
    if (sortedCards[i].getRank() == sortedCards[i + 1].getRank()) {
      return true;
    }
  }
  return false;
}

// Hand contains two different ranked pairs of cards; suit neglected
bool Hand::isTwoPair(const vector<Card> &sortedCards) const {
  int numPairs = 0;
  for (int i = 0; i < sortedCards.size() - 1; i++) {
    if (sortedCards[i].getRank() == sortedCards[i + 1].getRank()) {
      numPairs++;
      i++;
    }
  }
  return numPairs == 2;
}

// Hand contains three cards of the same rank; suit neglected
bool Hand::isThreeOfAKind(const vector<Card> &sortedCards) const {
  for (int i = 0; i < sortedCards.size() - 2; i++) {
    if (sortedCards[i].getRank() == sortedCards[i + 1].getRank() &&
        sortedCards[i].getRank() == sortedCards[i + 2].getRank()) {
      return true;
    }
  }
  return false;
}

// Hand contains four cards of the same rank; suit neglected
bool Hand::isFourOfAKind(const vector<Card> &sortedCards) const {
  for (int i = 0; i < sortedCards.size() - 3; i++) {
    if (sortedCards[i].getRank() == sortedCards[i + 1].getRank() &&
        sortedCards[i].getRank() == sortedCards[i + 2].getRank() &&
        sortedCards[i].getRank() == sortedCards[i + 3].getRank()) {
      return true;
    }
  }
  return false;
}

// Hand contains five cards of the same suit; rank neglected
bool Hand::isFlush(const vector<Card> &sortedCards) const {
  for (int i = 0; i < sortedCards.size() - 1; i++) {
    if (sortedCards[i].getSuit() != sortedCards[i + 1].getSuit()) {
      return false;
    }
  }
  return true;
}

// Hand contains a consecutively ranked five cards; suit neglected
bool Hand::isStraight(const vector<Card> &sortedCards) const {
  for (int i = 0; i < sortedCards.size() - 1; i++) {
    if (sortedCards[i].getRank() != sortedCards[i + 1].getRank() - 1) {
      return false;
    }
  }
  return true;
}

// Hand contains a pair of same ranked cards, as well as three cards of a
// different rank; suit neglected
bool Hand::isFullHouse(const vector<Card> &sortedCards) const {
  if (sortedCards[0].getRank() == sortedCards[1].getRank() &&
      sortedCards[3].getRank() == sortedCards[4].getRank() &&
      (sortedCards[2].getRank() == sortedCards[0].getRank() ||
       sortedCards[2].getRank() == sortedCards[3].getRank())) {
    return true;
  }
  return false;
}
// Hand contains five consecutively ranked cards, all of the same suit
bool Hand::isStraightFlush(const vector<Card> &sortedCards) const {
  return isStraight(sortedCards) && isFlush(sortedCards);
}

// Royal Flush is a special case of a Straight Flush
// The hand must be ranked '10,J,Q,K,A' of the same suit
bool Hand::isRoyalFlush(const vector<Card> &sortedCards) const {
  if (isStraightFlush(sortedCards) && sortedCards[4].getRank() == Card::ACE) {
    return true;
  }
  return false;
}

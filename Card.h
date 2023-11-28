/*
 *  Declaration of the Card class
 */

#ifndef CARD_H
#define CARD_H

#include <string>
using namespace std;

class Card {
public:
  enum Rank {
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE
  };                                             // All ranks enumeration
  enum Suit { HEARTS, CLUBS, DIAMONDS, SPADES }; // All suits enumeration

  Card();
  Card(Rank r, Suit s);
  Rank getRank() const;
  Suit getSuit() const;
  string toString() const;

private:
  Rank rank;
  Suit suit;
};
#endif // CARD_H

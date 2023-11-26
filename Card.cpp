/*
Card Class:
  - represents a playing card
  - a card can be ranked 2 - A and suited hearts, clubs, diamonds
*/
#include "Card.h"
#include <iostream>
using namespace std;

Card::Card() : rank(TWO), suit(HEARTS) {} // 2H - default constructor value
Card::Card(Rank r, Suit s) : rank(r), suit(s) {}

Card::Rank Card::getRank() const { return rank; }
Card::Suit Card::getSuit() const { return suit; }

std::string Card::toString() const {
  std::string ranks[] = {"2", "3",  "4", "5", "6", "7", "8",
                         "9", "10", "J", "Q", "K", "A"};
  std::string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
  // return ranks[rank] + " of " + suits[suit];
  // you also occassionaly get an exception here because sometimes a card has an
  // invalid rank, I didn't check how those ranks were set though.
  return ranks[static_cast<int>(rank)] + " of " + suits[static_cast<int>(suit)];
}

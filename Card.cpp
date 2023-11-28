/*
 *  Implementation of the Card class
 */
#include "Card.h"
#include <iostream>
using namespace std;

Card::Card()
    : rank(TWO), suit(HEARTS) {} // 2H - Arbitrary default constructor value
Card::Card(Rank r, Suit s) : rank(r), suit(s) {}

Card::Rank Card::getRank() const { return rank; }
Card::Suit Card::getSuit() const { return suit; }

string Card::toString() const {
  string ranks[] = {"2", "3",  "4", "5", "6", "7", "8",
                    "9", "10", "J", "Q", "K", "A"};
  string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
  return ranks[static_cast<int>(rank)] + " of " +
         suits[static_cast<int>(
             suit)]; // Card converted to string representation
}

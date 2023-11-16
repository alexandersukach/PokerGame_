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

void Card::display() const {
    // Map card ranks and suits to strings for output
    const char* rankStr[] = { "2 ", "3 ", "4 ", "5 ", "6 ", "7 ", "8 ", "9 ", "10 ", "J ", "Q ", "K ", "A " };
    const char* suitStr[] = { "\u2665", "\u2663", "\u2666", "\u2660" }; // H C D S
    cout << rankStr[rank] << suitStr[suit] << endl;
}


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
    // Assuming rank and suit are member variables of your Card class
    std::string ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    std::string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};

    return ranks[rank] + " of " + suits[suit];
}

void Card::display() const {
    std::cout << toString() << std::endl;
}

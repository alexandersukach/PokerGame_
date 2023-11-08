#include "Card.h"
#include <iostream>
using namespace std;

Card::Card() : rank(TWO), suit(HEARTS) {}
Card::Card(Rank r, Suit s) : rank(r), suit(s) {}

Card::Rank Card::getRank() const {
    return rank;
}
Card::Suit Card::getSuit() const {
    return suit;
}


void Card::display() const {
    const char* rankStr[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
    const char* suitStr[] = { "H", "C", "D", "S" };
    cout << rankStr[rank] << suitStr[suit] << endl;
}

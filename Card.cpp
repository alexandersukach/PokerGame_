#include "Card.h"
#include <iostream>

Card::Card(Rank r, Suit s) : rank(r), suit(s) {}

Card::Rank Card::getRank() const {
    return rank;
}
Card::Suit Card::getSuit() const {
    return suit;
}

/*
void Card::display() const {
    const char* rankStr[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
    const char* suitStr[] = { "H", "C", "D", "S" };
    std::cout << rankStr[rank] << suitStr[suit] << std::endl;
}
*/
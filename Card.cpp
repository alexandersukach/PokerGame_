#include "Card.h"
#include <iostream>
using namespace std;

Card::Card() : rank(TWO), suit(HEARTS) {} // 2H - default constructor value
Card::Card(Rank r, Suit s) : rank(r), suit(s) {}

Card::Rank Card::getRank() const { return rank; }
Card::Suit Card::getSuit() const { return suit; }

void Card::display() const {
    // Map card ranks and suits to strings for output
    const char* rankStr[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
    const char* suitStr[] = { "H", "C", "D", "S" };
    cout << rankStr[rank] << suitStr[suit] << endl;
}

/*
~/Desktop/PokerGame_> g++ -std=c++17 Card.cpp
Undefined symbols for architecture x86_64:
  "_main", referenced from:
     implicit entry/start for main executable
ld: symbol(s) not found for architecture x86_64
clang: error: linker command failed with exit code 1 (use -v to see invocation)
*/
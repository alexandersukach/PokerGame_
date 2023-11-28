// Player.cpp

#include "Player.h"
#include <iostream>

using namespace std;

Player::Player() {}

Player::Player(const string &playerName, int startingBalance, bool computer)
    : name(playerName), balance(startingBalance), currentBet(0), folded(false),
      isComputerPlayer(computer), checked(false), called(false) {}

int Player::getBalance() const { return balance; }

string Player::getName() const { return name; }

bool Player::isComputer() const { return isComputerPlayer; }

void Player::placeBet(int betAmount) {
  if (betAmount > 0) {
    balance -= betAmount;
    currentBet += betAmount;
    cout << "\nYou have bet." << endl;
    cout << "Your current bet: " << currentBet << endl << endl;
  } else {
    cout << "\nInvalid bet amount. Please try again." << endl;
  }
}

void Player::resetBet() { currentBet = 0; }

void Player::winBet(int pot) { balance += pot; }

int Player::getCurrentBet() const { return currentBet; }

bool Player::hasFolded() const { return folded; }

bool Player::hasChecked() const { return checked; }

bool Player::hasCalled() const { return called; }

void Player::call(int amountToCall) {
  if (amountToCall >= balance) {
    cout << "You're forced to go all-in!" << endl;
    placeBet(balance);
  } else {
    cout << "You call, next player..." << endl;
    placeBet(amountToCall);
    called = true;
  }
}

void Player::fold() { folded = true; }

void Player::raise(int raiseAmount) {
  if (raiseAmount >= balance) {
    cout << "You're forced to go all-in!" << endl;
    placeBet(balance);
  } else {
    cout << "You raised by " << raiseAmount << "; next player..." << endl;
    placeBet(raiseAmount);
  }
}

void Player::check() { checked = true; }

bool Player::operator==(const Player &other) const {
  // Define your comparison logic here based on your Player class attributes
  return this->getName() == other.getName() &&
         this->getBalance() == other.getBalance() /* && other comparisons */;
}
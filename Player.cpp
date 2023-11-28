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

// Places a bet and updates the current bet.
void Player::placeBet(int betAmount) {
  balance -= betAmount;
  currentBet += betAmount;
  cout << "\n" << getName() << " has bet." << endl;
  cout << "Current bet: " << currentBet << endl << endl;
}

void Player::resetBet() { currentBet = 0; }

void Player::winBet(int pot) { balance += pot; }

int Player::getCurrentBet() const { return currentBet; }

bool Player::hasFolded() const { return folded; }

bool Player::hasChecked() const { return checked; }

bool Player::hasCalled() const { return called; }

// Handles the player's call action.
void Player::call(int amountToCall) {

  if (amountToCall >= balance) {
    cout << getName() << " is forced to go all-in!" << endl;
    placeBet(balance);
  } else {
    cout << getName() << " calls, next player..." << endl;
    placeBet(amountToCall);
    called = true;
  }
}

void Player::fold() { folded = true; }

// Handles the player's raise action.
void Player::raise(int raiseAmount) {
  if (raiseAmount >= balance) {
    cout << getName() << " is forced to go all-in!" << endl;
    placeBet(balance);
  } else {
    cout << getName() << " raises by " << raiseAmount << "; next player..."
         << endl;
    placeBet(raiseAmount);
  }
}

void Player::check() { checked = true; }

// Defines the comparison logic based on Player attributes.
bool Player::operator==(const Player &other) const {
  return getName() == other.getName() && getBalance() == other.getBalance() &&
         isComputer() == other.isComputer();
}
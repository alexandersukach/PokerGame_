/*
 *  Implementation of the Player class
 */
#include "Player.h"
#include <iostream>

using namespace std;

Player::Player() {} // Default constructor

// Constructor parameterized with the player's name, their starting balance, and
// whether they are a computer or not.
Player::Player(const string &playerName, int startingBalance, bool computer)
    : name(playerName), balance(startingBalance), currentBet(0), folded(false),
      isComputerPlayer(computer), checked(false), called(false) {}

int Player::getBalance() const { return balance; }

string Player::getName() const { return name; }

bool Player::isComputer() const { return isComputerPlayer; }

// Updates the user's current bed and reduces their balance
void Player::placeBet(int betAmount) {
  balance -= betAmount;
  currentBet += betAmount;
}

// Reset the player's current bet to 0
void Player::resetBet() { currentBet = 0; }

void Player::winBet(int pot) { balance += pot; }

int Player::getCurrentBet() const { return currentBet; }

bool Player::hasFolded() const { return folded; }

bool Player::hasChecked() const { return checked; }

bool Player::hasCalled() const { return called; }

// I WILL NEED IS ALL IN LATER....

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

void Player::call() { called = true; }

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
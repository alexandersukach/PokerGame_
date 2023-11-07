#include "Player.h"

Player::Player() {
    // Initialize default values for the player here.
    name = "Default Name";
    balance = 0; // You can set any default balance you want
    currentBet = 0;
    isBigBlind = false;
    isSmallBlind = false;
    isFolded = false;
}

Player::Player(const std::string& playerName, int startingBalance) 
: name(playerName), balance(startingBalance), currentBet(0), isBigBlind(false), isSmallBlind(false), isFolded(false)  { }

int Player::getBalance() const { return balance; }

void Player::setBalance(int bet) { balance -= bet; }

int Player::getCurrentBet() const {
    return currentBet;
 }

void Player::winHand(int pot) { balance += pot; }

void Player::setCurrentBet(int betMade) { currentBet += betMade; } // How much player has bet so far

// void Player::getCurrentBet() { return currentBet; }

void Player::placeBet(int betAmount) { balance -= betAmount; currentBet += betAmount; }

void Player::raise(int raiseAmount) { balance -= raiseAmount; }

void Player::fold() { isFolded = true; }
// bool Player::isInGame() const { return inGame; } Maybe in addition to fold()

void Player::bigBlindPayment() { balance -= 10; }

void Player::smallBlindPayment() { balance -= 5; }

void Player::bigBlind() { isBigBlind = true; }

void Player::smallBlind() { isSmallBlind = true; }

// void cpuAction
/*
    void cpuAction(bool isRaiseMade) {
        double betProbability;
        double callProbability;
        double raiseProbability;
        double foldProbability;
    }*/

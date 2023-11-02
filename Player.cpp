#include "Player.h"

Player::Player(const std::string& playerName, int startingBalance) 
: name(playerName), balance(startingBalance), currentBet(0), isBigBlind(false), isSmallBlind(false), isFolded(false)  { }

int Player::getBalance() const { return balance; }

void Player::winHand(int pot) { balance += pot; }

void Player::setCurrentBet(int betMade) { currentBet += betMade; } // How much player has bet so far

// void Player::getCurrentBet() { return currentBet; }

void Player::placeBet(int betAmount) { balance -= betAmount; }

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

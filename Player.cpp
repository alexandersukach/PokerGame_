#include "Player.h"

Player::Player() {
    // Initialize default values for the player here.
    name = "Default Name";
    balance = 0.00; // You can set any default balance you want
    currentBet = 0.00;
    isBigBlind = false;
    isSmallBlind = false;
    isFolded = false;
    isComputerPlayer = false;

}

Player::Player(const std::string& playerName, double startingBalance) 
: name(playerName), balance(startingBalance), currentBet(0), isBigBlind(false), isSmallBlind(false), isFolded(false), isComputerPlayer(false) { }

double Player::getBalance() const { return balance; }

void Player::setBalance(double bet) { balance -= bet; }

bool Player::isComputer() const { return isComputerPlayer; }

 void Player::winHand(double pot) { balance += pot; }

//void Player::setCurrentBet(int betMade) { currentBet += betMade; } // How much player has bet so far

 int Player::getCurrentBet() { return currentBet; }

void Player::placeBet(double betAmount) { balance -= betAmount; currentBet += betAmount; }

void Player::raise(double raiseAmount) { balance -= raiseAmount; }

void Player::fold() { isFolded = true; }
// bool Player::isInGame() const { return inGame; } Maybe in addition to fold()

bool Player::hasFolded() { return isFolded; }
void Player::bigBlindPayment() { balance -= 10; }

void Player::smallBlindPayment() { balance -= 5; }

void Player::setBigBlind() { isBigBlind = true; }

void Player::setSmallBlind() { isSmallBlind = true; }

// void cpuAction
/*
    void cpuAction(bool isRaiseMade) {
        double betProbability;
        double callProbability;
        double raiseProbability;
        double foldProbability;
    }*/

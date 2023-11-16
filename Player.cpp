/*
Player Class:
    - represents 1 of a maximum 5 player in the Poker game
    - there is only one human player and the remaining are computers
*/
#include "Player.h"
#include <string>
using namespace std;

Player::Player() {}
// Player initialized with a name, starting balance, and indicator of whether a CPU or not
Player::Player(const string& playerName, double startingBalance, bool computer) 
: name(playerName), balance(startingBalance), currentBet(0), isFolded(false), isComputerPlayer(computer), smallBlind(false), bigBlind(false) { }
double Player::getBalance() const { return balance; }
string Player::getName() const { return name; }
bool Player::isComputer() const { return isComputerPlayer; }
void Player::placeBet(double betPlaced) { balance -= betPlaced; currentBet += betPlaced; }
void Player::winBet(double pot) { balance += pot; }
double Player::getCurrentBet() const { return currentBet; }
void Player::raise(double raiseAmount) { balance -= raiseAmount; currentBet += raiseAmount; }
void Player::fold() { isFolded = true; }
bool Player::hasFolded() const { return isFolded; }
void Player::setBigBlind() { bigBlind = true; }
bool Player::isBigBlind() { return bigBlind; }
void Player::setSmallBlind() { smallBlind = true; }
bool Player::isSmallBlind() { return smallBlind; }

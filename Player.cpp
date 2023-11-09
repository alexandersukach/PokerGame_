#include "Player.h"
#include <string>
using namespace std;

Player::Player() {};
Player::Player(const string& playerName, double startingBalance) 
: name(playerName), balance(startingBalance), currentBet(0), isFolded(false), isComputerPlayer(false) { }
double Player::getBalance() const { return balance; }
string Player::getName() const { return name; }
bool Player::isComputer() const { return isComputerPlayer; }
void Player::placeBet(double betPlaced) { balance -= betPlaced; currentBet += betPlaced; }
void Player::winBet(double pot) { balance += pot; }
 int Player::getCurrentBet() { return currentBet; }
void Player::raise(double raiseAmount) { balance -= raiseAmount; currentBet += raiseAmount; }
void Player::fold() { isFolded = true; }
bool Player::hasFolded() { return isFolded; }
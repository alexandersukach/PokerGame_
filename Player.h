/*
 *  Declaration of the Player class.
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <string>

using namespace std;

class Player {
private:
  string name;
  int balance;
  int currentBet;
  bool folded;
  bool isComputerPlayer;
  bool checked;
  bool called;

public:
  Player();
  Player(const string &playerName, int startingBalance, bool computer);

  int getBalance() const;
  string getName() const;
  bool isComputer() const;

  // Betting actions
  void placeBet(int betAmount);
  void winBet(int pot);

  int getCurrentBet() const;
  bool hasFolded() const;
  bool hasChecked() const;
  bool hasCalled() const;

  void resetBet();

  // Player actions during the game
  void call(int amountToCall);
  void call();
  void fold();
  void raise(int raiseAmount);
  void check();

  // Comparison operator
  bool operator==(const Player &other) const;
};

#endif // PLAYER_H
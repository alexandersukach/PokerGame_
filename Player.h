// Player.h

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
  string playerName;

public:
  Player();
  Player(const string &playerName, int startingBalance, bool computer);

  int getBalance() const;
  string getName() const;
  bool isComputer() const;
  void placeBet(int betAmount);
  void resetBet();
  void winBet(int pot);
  int getCurrentBet() const;
  bool hasFolded() const;
  bool hasChecked() const;
  bool hasCalled() const;

  void call(int amountToCall);
  void fold();
  void raise(int raiseAmount);
  void check();

  bool operator==(const Player &other) const;
};

#endif // PLAYER_H

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;

class Player {
private:
  string name;
  int balance, currentBet;
  bool isComputerPlayer, bigBlind, smallBlind, isFolded, ifBet;
  bool isChecked;

public:
  Player();
  Player(const string &playerName, double startingBalance, bool isComputer);
  double getBalance() const;
  string getName() const;
  bool isComputer() const;
  void placeBet(double betPlaced); // setBalance and setCurrentBet
  void resetBet();
  bool hasBet();
  void winBet(double betWon); // setBalance
  // double getCurrentBet();
  double getCurrentBet() const;
  // void setCurrentBet(double addedBet){};
  void raise(double raiseAmount);

  void fold();
  bool hasFolded();

  bool hasChecked() const { return isChecked; };
  void check(bool checked) { isChecked = checked; };

  void setBigBlind();
  bool isBigBlind();

  void setSmallBlind();
  bool isSmallBlind();
  // void cpuAction(bool isRaiseMade);
  // bool isFolded();
  bool operator==(const Player &other) const;
};

#endif // PLAYER_H
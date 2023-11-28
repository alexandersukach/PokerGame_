#ifndef BETTINGROUND_H
#define BETTINGROUND_H

#include "Player.h"
#include <queue>

using namespace std;

class BettingRound {
private:
  queue<Player> players;
  int pot;
  int currentRoundBet;
  bool isBetMade;
  bool isRaiseMade;
  bool isReRaiseMade;
  queue<Player> activePlayers;

public:
  BettingRound(queue<Player> playerQueue);
  void playRound();
  bool allPlayersChecked() const;
  bool allPlayersCalled() const;
  // void handleRaiseMadePlayerActions(Player &user);

  void handleBet(Player &user, int amountToBet);
  void handleRaise(Player &user, int amountToBet);

  void handleNoBetMadePlayerActions(Player &user);
  void handleBetMadePlayerActions(Player &user);
  void handleRaiseMadePlayerActions(Player &user);
  void handleBetMadeCPUActions(Player &computerPlayer);
  void handleRaiseMadeCPUActions(Player &computerPlayer);
  void handlePlayerActions(Player &computerPlayer);
  void handleCPUActions(Player &computerPlayer);
  void handleNoBetMadeCPUActions(Player &computerPlayer);
  int getPot();
};

#endif // BETTINGROUND_H

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
  int minRoundBet = 10.00;
  bool isBetMade;
  bool isRaiseMade;
  bool isReRaiseMade;
  queue<Player> activePlayers;

public:
  BettingRound(std::queue<Player> playerQueue, int minBet);
  void playRound();
  bool allPlayersChecked() const;

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

#ifndef BETTINGROUND_H
#define BETTINGROUND_H

#include "Player.h"
#include <queue>

class BettingRound {
private:
  std::queue<Player> players;
  double pot;
  double currentRoundBet;
  double minRoundBet = 10.00;
  bool isBetMade;
  bool isRaiseMade;
  bool isReRaiseMade;
  std::queue<Player> activePlayers;

public:
  // Constructor with a queue of players
  BettingRound(const std::queue<Player> &roundPlayers, double minBet);

  void playRound();
  void handleNoBetMadePlayerActions(Player &user);
  void playerRaisesAction(Player &user);
  void handleBetMadePlayerActions(Player &user);
  void handleRaiseMadePlayerActions(Player &user);
  // void handleReRaiseMadePlayerActions(Player& user);
  void handleNoBetCPUActions(Player &computerPlayer);
  void handleCPUActions(Player &computerPlayer);

  bool allPlayersFinishedBetting() const;
  bool allPlayersChecked() const;

  double getPot();
};

#endif // BETTINGROUND_H

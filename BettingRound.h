#ifndef BETTINGROUND_H
#define BETTINGROUND_H

#include <queue>
#include "Player.h"

class BettingRound {
private:
    std::queue<Player> players;
    double pot;
    double currentRoundBet;
    double minRoundBet = 10.00;
    bool isBetMade;
    bool isRaiseMade;
    bool isReRaiseMade;

public:
    // Constructor with a queue of players
    BettingRound(std::queue<Player>& roundPlayers, double minBet);

    void playRound();
    void handleNoBetMadePlayerActions(Player& user);
    void handleBetMadePlayerActions(Player& user);
    void handleRaiseMadePlayerActions(Player& user);
    //void handleReRaiseMadePlayerActions(Player& user);
    void handleCPUActions(Player& computerPlayer);
    bool makeBet(Player& user);
    bool allPlayersFinishedBetting() const;
};

#endif // BETTINGROUND_H

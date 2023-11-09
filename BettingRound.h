#ifndef BETTINGROUND_H
#define BETTINGROUND_H
#include <queue>
#include "Player.h"
using namespace std;

class BettingRound {
    private:
        queue<Player> players;
        double pot;
        double currentRoundBet;
        double minRoundBet = 10.00;
        bool isBetMade;
        bool isRaiseMade;
       // bool isReRaiseMade; // Unsure of whether I am including


public:
    BettingRound(queue<Player>& roundPlayers) : players(roundPlayers), pot(0), currentRoundBet(0), isBetMade(false), isRaiseMade(false) {}
    void playRound();
    void handleNoBetMadePlayerActions(Player& user);
    void handleBetMadePlayerActions(Player& user);
    void handleRaiseMadePlayerActions(Player& user);
    void handleCPUActions(Player& computerPlayer);
    //void removePlayerIfBalanceZero();
};

#endif // BETTINGROUND_H
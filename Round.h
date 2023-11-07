#ifndef ROUND_H
#define ROUND_H
#include <queue>
#include "Player.h"
using namespace std;

class Round {
    private:
        queue<Player> players;
        int pot;
        int currentRoundBet;
        bool isBetMade;
        bool isRaiseMade;
        bool isReRaiseMade;

public:
    Round(queue<Player>& players);

    void playRound();
    void handleNoBetYetPlayerActions(Player& user);
    void handleBetMadePlayerActions(Player& user);
    void handleRaiseMadePlayerActions(Player& user);
    void handleCpuActions(Player& computerPlayer);
    void removePlayerIfBalanceZero();
};

#endif // ROUND_H
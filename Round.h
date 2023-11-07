#ifndef ROUND_H
#define ROUND_H
#include <queue>
#include "Player.h"
using namespace std

class Round {
    private:
        queue<Player> players;
        int pot;
        int currentRoundBet;
        bool isBetMade;
        bool isRaiseMade;
        bool isReRaiseMade;

public:
    Round(int number, queue<Player>& players, roundPlayers);

    void playRound();
    void handleBetMadeActions();
    void handleNoBetActions();
    void initialBetAmount(int initialRoundBet);
    void handleBetMadePlayerActions();
    void handleNoBetPlayerActions();
    void handleCPUPlayerActions();
};

#endif // ROUND_H
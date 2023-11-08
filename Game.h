#ifndef GAME_H
#define GAME_H
#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include <string>
#include <queue>
using namespace std;



class Game {
    private:
        Card communityCards[5]; // 5 total
        Card playerHoleCards[5][2]; // [playerIndex][card]
        Card combinedHand[5][7]; //[playerIndex][card]
        queue<Player> players;
        Deck gameDeck;
        Player userPlayer;
        Player* dealer;
        //int currentTurn;
        //bool isGameOver = false;
        //bool isHandOver = false;

    public:
        Game(const string& userName, double usersBalance);

        void initializePlayers(const string& playerName, double usersBalance);
        void dealHoleCards();
        void dealFlop();
        void dealTurn() {};
        void dealRiver() {};
        void combineHands() {};
        void rotateDealer() {};
};


#endif // GAME_H
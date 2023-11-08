#ifndef GAME_H
#define GAME_H
#include "Card.h"
#include "Deck.h"
#include "Player.h" // Include any other necessary headers here
#include <string>
#include <queue>

using namespace std;

class Game {
    public:
        Game(const string& userName, double userStartingBalance);
    void initializePlayers(const string& userName, double playerBalance);
        void dealHoleCards(queue<Player>& activePlayers, Deck& roundDeck);
        void dealFlop(Deck& roundDeck);
        void dealTurn(Deck& roundDeck);
        void dealRiver(Deck& roundDeck);
        void combineHands();
        void rotateDealer();
        void displayRules();
        void displayHandRankings();
        void compareHands();
        
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
};


#endif // GAME_H
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
        Card Game::communityCards[5]; // 5 total
        Card Game::playerHoleCards[5][2]; // [playerIndex][card]
        Card Game::combinedHand[5][7]; //[playerIndex][card]
        std::queue<Player> players;
        Deck gameDeck;
        Player userPlayer;

    public:
        Game(const std::string& userName, int userStartingBalance);

        void initializePlayers(const std::string& playerName, int startingBalance) { };
        void dealHoleCards() {};
        void dealFlop() {};
        void dealTurn() {};
        void dealRiver() {};
        //Maybe I could make those into a loop

        void combineHands() {};
        void rotateDealer() {};


        //TOO LAZY TO SWITCH CLASS

       
        /*
        This is where we go for the hand class...
        Should I have established them as Hand<Card>
        */
};


#endif // GAME_H
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


/*
Each game has finite # of betting rounds
oh so round has nothing to do with that
I should have players defined outside of game();
okay yes... and does this mean initializePlayers
would be just outside....like i could make new game after 
each few rounds, but it technically all be one 
one game...I'm gonna have to redraw a strategy....
fuck

// how can we instantiate deck within same game...
I should leave the rounds class to just the betting side
while the game class is more what's actually happening...
Aka things in game are necessary while technically
everyone could check...yknow

I need to make a userPlayer() where is they bust,
the game is over....isBusted flag in Player class?
Also, if computer busts, have to make sure to take him out


I want the current pot and best displayed 
has anyone thought of sending a game (program) where
it can say run on terminal and change the color?


Any time a game is created,
the deck is created, shuffled, and cut.
Two cards are dealt out to each pleayer, 
which are to be their respective hole cards.
The dealer then burns a card, and shows
three cards which become community cards.
A round of betting ensues.
The dealer then burns a card, and shows
one card, adding to the community cards.
A round of betting ensues.
The dealer then burns a card, and shows
one card, adding to the community cards (reached max).
Players mix and match their two cards with the five
community cards to create the strongest hand (see ranking).

*/


#endif // GAME_H
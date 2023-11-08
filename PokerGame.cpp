#include "Game.h"
#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include "Round.h"
#include "DoublyLinkedList.h"
#include "Player.h"

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
using namespace std;



int main() {
        string userName;
        cout << "\nWhat is your name? ";
        cin >> userName;
    int numOpponents;
        cout << "How many opponents would you like to play against(max 4)? ";
        cin >> numOpponents;

    double buyIn;
        cout << "Provide buyIn value for everyone: $";
        cin >> buyIn;

    Game pokerGame(userName, buyIn);
    Deck gameDeck;
    Player userPlayer = Player(userName, buyIn);
    // while player's balance > 0
    // create new round and add players (which are those that didn't fold last round)
    // deal cards until all hands are complete
    // determine winner of each hand
    queue<Player> players;
    players.push(userPlayer); // player User
    for (int i = 0; i < numOpponents; i++) {
        string opponentName = "CPU " + to_string(0 + 1);
        players.push(Player(opponentName, buyIn));
    }



    pokerGame.displayRules();
    pokerGame.displayHandRankings();

    bool gameOver = false;
    while (!gameOver) {
        // deal, bet, deal, bet, but I need another condition....for every 4 bet rounds?, keep same
        // game but determine winner and reset deck, unless user's balance is 0, in which case
        // gameOver = true;
        if (userPlayer.getBalance() == 0) {
            gameOver = true;
        }
    }

/*
    End while loop determine game;
*/
//Modify the Round class to add a queue for players who folded in the current hand:


    return 0;
}
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
    cout << "How many opponents would you like to play against (max 4)? ";
    cin >> numOpponents;

    double buyIn;
    cout << "Provide buyIn value for everyone: $";
    cin >> buyIn;

    Game pokerGame(userName, buyIn);
    Deck gameDeck;
    pokerGame.displayRules();
    pokerGame.displayHandRankings();
    Player userPlayer = Player(userName, buyIn);

    // Create a queue of all players including the user and opponents
    queue<Player> players;
    players.push(userPlayer); // User
    for (int i = 0; i < numOpponents; i++) {
        string opponentName = "CPU " + to_string(i + 1); // Fix the opponent names
        players.push(Player(opponentName, buyIn));
    }

    bool gameOver = false;
    while (!gameOver) {
        queue<Player> activePlayers;
        while (!players.empty()) {
            Player currentPlayer = players.front();
            players.pop();
            if (!currentPlayer.hasFolded()) {
                activePlayers.push(currentPlayer);
            }
        }
        pokerGame.dealHoleCards(activePlayers, gameDeck);
        Round bettingRound1(activePlayers);
        bettingRound1.playRound();

        pokerGame.dealFlop(gameDeck);
        Round bettingRound2(activePlayers);
        bettingRound2.playRound();
        
        pokerGame.dealTurn(gameDeck);
        Round bettingRound3(activePlayers);
        bettingRound3.playRound();

        pokerGame.dealRiver(gameDeck);
        Round bettingRound4(activePlayers);
        bettingRound4.playRound();


        if (userPlayer.getBalance() == 0) {
            gameOver = true;
        }
    }

    // End of the game logic
    return 0;
}

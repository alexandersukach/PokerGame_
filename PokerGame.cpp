#include "Game.h"

#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include "Round.h"
#include "DoublyLinkedList.h"
#include "string.h"
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
    // Auto play against 4 people

    double buyIn;
    cout << "Provide buyIn value for everyone: $";
    cin >> buyIn;

    Game pokerGame(userName, buyIn);
    pokerGame.displayRules();
    pokerGame.displayHandRankings();
    Player userPlayer = Player(userName, buyIn);

    // Create a queue of all players including the user and opponents
    queue<Player> players;
    players.push(userPlayer); // User
    for (int i = 0; i < 4; i++) {
        string opponentName = "CPU " + to_string(i + 1); // Fix the opponent names
        players.push(Player(opponentName, buyIn));
    }

    bool gameOver = false;
    while (!gameOver) {
        queue<Player> activePlayers;
        Deck gameDeck = Deck();
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

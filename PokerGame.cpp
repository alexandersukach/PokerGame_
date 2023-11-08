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
    Deck gameDeck();

    queue<Player> players;
    players.push(Player(userName, buyIn));
    for (int i = 0; i < numOpponents; i++) {
        string opponentName = "CPU " + to_string(0 + 1);
        players.push(Player(opponentName, buyIn));
    }

    pokerGame.displayRules();
    pokerGame.displayHandRankings();


//Modify the Round class to add a queue for players who folded in the current hand:


    return 0;
}
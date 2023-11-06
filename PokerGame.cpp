#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>
#include <vector>
#include <stack>
#include <string>
#include <cctype> 
#include <queue>
#include <algorithm>
#include <random>

#include "Card.h"
#include "Player.h"
#include "Hand.h"
#include "Deck.h"
#include "DoublyLinkedList.h"
#include "Game.h"
using namespace std;





//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main() {
    int pot = 0;

    //If big blind remove 10 if small blind remove 5 add to pot...
    int numOpponents;
    cout << "Enter number of players, other than yourself: ";
    cin >> numOpponents;

    string userName;
    cout << "Enter your name: ";
    cin >> userName;

    int userStartingBalance; // The same for all players
    cout << "Enter your starting balance: ";
    cin >> userStartingBalance;
    
    Game game(userName, userStartingBalance);

    //game.initializePlayers(numOpponents, userName, userStartingBalance);
    //Necessary
    game.dealHoleCards();
    
    game.dealFlop();

    game.dealTurn();

    game.dealRiver();


bool isBigBlind, isSmallBlind;
if (!isBigBlind) {
    if(isSmallBlind) {
        char actionSmallBlind;
        cout << "Would you like to (c)all $5 or (f)old?";
        cin >> actionSmallBlind;
        actionSmallBlind = tolower(actionSmallBlind);
        switch (actionSmallBlind) {
            case 'c': {
                userPlayer.placeBet(5);
                break;
            case 'f': {
                userPlayer.fold();
                break;
            default:
                cout << "Choose valid option";
            }
            }
        }
    }
}

bool betMade;
int betToBeCalled;
if(betMade) {
    char actionBetMade;
    cout << "Would you like to (c)all, (f)old, or (r)aise?";
    cin >> actionBetMade;
    actionBetMade = tolower(actionBetMade);
    switch(actionBetMade) {
        case 'c':
            userPlayer.placeBet(betToBeCalled);
            break;
        case 'f':
            userPlayer.fold();
            break;
        case 'r':
            userPlayer.reraise();
            //betTobeCalled = the reraise //need to do some math to subtract so other players know what to put in
            break;
        default:
            cout << "Choose valid option";
    }
}
// no bet made
else {
    char actionNoBetMade;
    cout << "Would you like to (b)et, (c)heck?";
    cin >> actionNoBetMade;;
    actionNoBetMade = tolower(actionNoBetMade);
    switch(actionNoBetMade) {
        case 'b':
        
} }




}
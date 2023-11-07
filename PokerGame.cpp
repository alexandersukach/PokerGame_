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

void displayRules() {
    cout << "=====================================" << endl;
    cout << "      Texas Hold'em Poker Rules      " << endl;
    cout << "=====================================" << endl;
    cout << "1.) Start by specifying the buy-in amount at the beginning of the game." << endl;
    cout << "2.) The game uses standard blinds: $5 for the small blind and $10 for the big blind." << endl;
    cout << "   Blinds ensure there is always money in the pot to compete for." << endl;
    cout << "3.) The player to the immediate left of the dealer assumes the role of the small blind." << endl;
    cout << "4.) The player to the left of the small blind takes on the role of the big blind." << endl;
    cout << "5.) During each round of betting, players can choose from various actions, including checking," << endl;
    cout << "   betting, calling, or raising, depending on the game situation." << endl;
    cout << "6.) Starting with the small blind and proceeding clockwise, each player receives two 'hole cards'" << endl;
    cout << "   which remain concealed from others." << endl;
    cout << "7.) Players engage in a round of betting based on their hole cards and the community cards revealed later." << endl;
    cout << "8.) Before revealing the community cards, a card is 'burned' or removed from the deck for fairness." << endl;
    cout << "   Subsequently, three cards are placed face up on the board, collectively known as 'the flop'." << endl;
    cout << "9.) Following the flop, another round of betting ensues." << endl;
    cout << "10.) The game proceeds to the next stage by 'burning' another card and revealing 'the turn' card." << endl;
    cout << "11.) Another round of betting follows the turn." << endl;
    cout << "12.) Another 'burn' is performed, and 'the river' card is disclosed." << endl;
    cout << "13.) The final round of betting takes place, and players try to form their best 5-card hand," << endl;
    cout << "   utilizing both their 'hole cards' and the 'community cards' on the board." << endl;
    cout << "   For your convenience, hand rankings are displayed to assist you." << endl;
    cout << "14.) If players have equal hands, a 'chop pot' occurs. In such cases, each player's kicker card, which is their" << endl; 
    cout << "   second hole card, may be examined to determine the winner." << endl;
}


int main() {
    double pot = 0.00;
    int numOpponents = 5;
    string userName;
    double userStartingBalance;

    cout << "Enter your name: ";
    cin >> userName;

    cout << "\nEnter starting balance for all players: ";
    cin >> userStartingBalance;

    Game pokerGame(userName, userStartingBalance);
    
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*

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




}*/
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

//#include "Card.h"
//#include "Player.h"
//#include "Hand.h"
//#include "Deck.h"
//#include "DoublyLinkedList.h"
//#include "Game.h"
using namespace std;

void displayRules() {
    cout << "                 =====================================" << endl;
    cout << "                       Texas Hold'em Poker Rules      " << endl;
    cout << "                 =====================================" << endl;
    cout << "- Start by specifying the buy-in amount at the beginning of the game." << endl;
    cout << "- The game uses standard blinds: $5 for the small blind and $10 for" << endl;
    cout << "  the big blind." << endl;
    cout << "  Blinds ensure there is always money in the pot to compete for." << endl;
    cout << "- The player to the immediate left of the dealer assumes the role " << endl;
    cout << " of the small blind." << endl;
    cout << "- The player to the left of the small blind takes on the role of the " << endl;
    cout << "  big blind." << endl;
    cout << "- During each round of betting, players can choose from various actions, " << endl;
    cout << "  including checking, betting, calling, or raising, depending on the" << endl;
    cout << "  game situation." << endl;
    cout << "- Starting with the small blind and proceeding clockwise, each player " << endl;
    cout << "  receives two 'hole cards' which remain concealed from others." << endl;
    cout << "- Players engage in a round of betting based on their hole cards and" << endl;
    cout << "  community cards to be revealed." << endl;
    cout << "- A card is then 'burned', or removed from the deck." << endl;
    cout << "- The subsequent three cards are placed face up on the board (the flop). " << endl;
    cout << "- Following the flop, another round of betting ensues." << endl;
    cout << "- A card is then 'burned' and the next card is placed face up (the turn)." << endl;
    cout << "- Another round of betting follows the turn." << endl;
    cout << "- A final card is then 'burned' and (the river) card is drawn following" << endl;
    cout << "  it, which completes the set of community cards." << endl;
    cout << "- The final round of betting takes place, and players try to form their " << endl;
    cout << "  best 5-card hand, utilizing both their 'hole cards' and the 'community " << endl;
    cout << "  cards' on the table." << endl;
    cout << "  For your convenience, hand rankings are displayed to assist you." << endl;
    cout << "- If players have equal hands, a 'chop pot' occurs. In such cases, " << endl;
    cout << "  each player's kicker card, which is their second hole card, may be " << endl;
    cout << "  examined to determine the winner." << endl << endl;
}

const std::string RED_TEXT = "\033[31m"; // Red text color
const std::string BLACK_TEXT = "\033[30m"; // Black text color
const std::string RESET_COLOR = "\033[0m"; // Reset text color to default
void displayHandRankings() {
    // Set a fixed width for card strings to ensure alignment
    const int cardWidth = 6;

    cout << "================ Hand Rankings ================" << endl;
    cout << "             (Strongest to weakest)" << endl;
    cout << "Royal Flush:" << "       " << BLACK_TEXT << left << setw(cardWidth) << "AS" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "KS" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "QS" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "JS" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "10S" << RESET_COLOR << endl;
    cout << "Straight Flush:" << "    " << RED_TEXT << left << setw(cardWidth) << "8H" << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << "7H" << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << "6H" << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << "5H" << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << "4H" << RESET_COLOR << endl;
    cout << "Four of a Kind:" << "    " << BLACK_TEXT << left << setw(cardWidth) << "7C" << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << "7D" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "7S" << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << "7H" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "3C" << RESET_COLOR << endl;
    cout << "Full House:" << "        " << RED_TEXT << left << setw(cardWidth) << "QH" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "QC" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "QS" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "4S" << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << "4H" << RESET_COLOR << endl;
    cout << "Flush:" << "             " << BLACK_TEXT << left << setw(cardWidth) << "4C" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "JS" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "AS" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "7C" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "9C" << RESET_COLOR << endl;
    cout << "Straight:" << "          " << BLACK_TEXT << left << setw(cardWidth) << "QC" << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << "JD" << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << "10H" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "9C" << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << "3H" << RESET_COLOR << endl;
    cout << "Three of a Kind:" << "   " << RED_TEXT << left << setw(cardWidth) << "KH" << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << "KD" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "KS" << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << "10H" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "7S" << RESET_COLOR << endl;
    cout << "Two Pair:" << "          " << BLACK_TEXT << left << setw(cardWidth) << "8S" << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << "8H" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "5S" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "5C" << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << "3H" << RESET_COLOR << endl;
    cout << "One Pair:" << "          " << BLACK_TEXT << left << setw(cardWidth) << "10C" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "10S" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "7C" << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << "4H" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "2C" << RESET_COLOR << endl;
    cout << "High Card:" << "         " << RED_TEXT << left << setw(cardWidth) << "AH" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "QC" << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << "10H" << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << "7C" << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << "4D" << RESET_COLOR << endl;
    cout << "===============================================" << endl;
}




/*
    double pot = 0.00;
    int numOpponents = 5;
    string userName;
    double userStartingBalance;

    cout << "Enter your name: ";
    cin >> userName;

    cout << "\nEnter starting balance for all players: ";
    cin >> userStartingBalance;

    Game pokerGame(userName, userStartingBalance);

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
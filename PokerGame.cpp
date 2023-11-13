#include "Game.h"

#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include "BettingRound.h"
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
    cout << "  For your convenience, hand rankings can be accessed at any time to assist you." << endl;
    cout << "- If players have equal hands, a 'chop pot' occurs. In such cases, " << endl;
    cout << "  each player's kicker card, which is their second hole card, may be " << endl;
    cout << "  examined to determine the winner." << endl << endl;
}

void displayHandRankings() {
    const int cardWidth = 6;
    const string RED_TEXT = "\033[31m"; // Red text
    const string BLACK_TEXT = "\033[30m"; // Black text 
    const string RESET_COLOR = "\033[0m"; // Default text

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

void updateActivePlayers(queue<Player>& activePlayers) {
    queue<Player> temp;
    while (!activePlayers.empty()) {
        Player currentPlayer = activePlayers.front();
        activePlayers.pop();
        if (!currentPlayer.hasFolded()) {
            temp.push(currentPlayer);
        }
    }
    activePlayers = temp;
}

int main() {
    displayRules();

    cout << "What is your name? ";
    string userName;
    cin >> userName;
    cout << "What would you like to buy-in for? ";
    double amountToBuyIn;
    cin >> amountToBuyIn;

    Game pokerGame(userName, amountToBuyIn); // if I'm initializing userPlayer, should initializePlayers just be initializeComputers 
    Player userPlayer = Player(userName,amountToBuyIn);
    // if user presses q, displayHandRankings() 
    bool gameOver = false;

    // 
    while (!gameOver) {

        Deck gameDeck = Deck(); // New deck, every poker round: initialized, shuffled, and cut
        // need active players queue here...
        queue<Player> activePlayers;
        // need a hand for each player here too.
        // establish that the head of queue is smallblind, then next is bigblind..
        // should i make own round for preflop, where blinds are in consideration
        pokerGame.dealHoleCards(activePlayers, gameDeck);
        BettingRound preFlop(activePlayers);
        preFlop.playRound();
        updateActivePlayers(activePlayers);

        pokerGame.dealFlop(gameDeck);
        BettingRound postFlop(activePlayers);
        postFlop.playRound();
        updateActivePlayers(activePlayers);

        pokerGame.dealTurn(gameDeck);
        BettingRound postTurn(activePlayers);
        postTurn.playRound();
        updateActivePlayers(activePlayers);

        pokerGame.dealRiver(gameDeck);
        BettingRound postRiver(activePlayers);
        postRiver.playRound();
        

        // After the river/bets settled, unless a player has no money, readd everyone to the queue, shift it clockwise and keep going yknow...

        // At this point, hands are compared...winner determined....
        // Bets are settled...etc....
        
        // I don't believe userPlayer is in the correct place...
        if (userPlayer.getBalance() == 0) {
            gameOver = true;                                                                                       
        }

        // Reset everything here...
        // Reset deck, reset queue of players to what is was (long so they're still in the game)
        // reset rounds...etc

    }
}



/*


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
*/
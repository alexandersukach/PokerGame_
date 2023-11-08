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
#include <map>
using namespace std;


    Game::Game(const string& userName, double userStartingBalance) : gameDeck() {
   initializePlayers(userName, userStartingBalance);

}

 void Game::initializePlayers(const string& userName, double playerBalance) {
    Player userPlayer = Player(userName, playerBalance);
    const int numComputerPlayers = 4;
    players.push(userPlayer);

    for (int i = 0; i < numComputerPlayers; i++) {
        string computerName = "Computer Player " + to_string(i + 1);
        players.push(Player(computerName, playerBalance));  // All players start with the same balance
    }
    // Set the initial dealer
    dealer = &players.front();
}

void Game::dealHoleCards(queue<Player>& activePlayers, Deck& roundDeck) {
    for (int cardIndex = 0; cardIndex < 2; cardIndex++) {
        for (int playerIndex = 0; playerIndex < activePlayers.size(); playerIndex++) {
            Player& player = activePlayers.front(); 
            playerHoleCards[playerIndex][cardIndex] = roundDeck.dealCard();
            activePlayers.push(player);
            activePlayers.pop();
        }
    }
}

        // BETTING ROUND 1

    void Game::dealFlop(Deck& roundDeck) {
        roundDeck.burnCard();
        for (int i = 0; i < 3; i++) {
            Card dealtCard = gameDeck.dealCard();
            communityCards[i] = dealtCard;
        }
    }
        // BETTING ROUND 2
    void Game::dealTurn(Deck& roundDeck) {
        roundDeck.burnCard();
        Card dealtCard = gameDeck.dealCard();
        communityCards[3] = dealtCard;
    }
        // BETTING ROUND 3
    void Game::dealRiver(Deck& roundDeck) {
        roundDeck.burnCard();
        Card dealtCard = gameDeck.dealCard();
        communityCards[4] = dealtCard;
    }
        // BETTING ROUND 4
    // Combining community cards and each player's cards to compare hand strength

void Game::combineHands() {
    for (int playerIndex = 0; playerIndex < players.size(); playerIndex++) {

        for (int i = 0; i < 2; i++) {
            combinedHand[playerIndex][i] = playerHoleCards[playerIndex][i];
        }

        for (int i = 2; i < 7; i++) {
            combinedHand[playerIndex][i] = communityCards[i - 2];
        }
    }
}

void Game::rotateDealer() {
        Player dealerPlayer = players.front();
        players.pop();
        players.push(dealerPlayer);
    }

void Game::displayRules() {
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

const string RED_TEXT = "\033[31m"; // Red text
const string BLACK_TEXT = "\033[30m"; // Black text 
const string RESET_COLOR = "\033[0m"; // Default text
void Game::displayHandRankings() {
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

string Game::mapScoreToHand(int score) {
    if (score == 10) {
        return "Royal Flush";
    } else if (score == 9) {
        return "Straight Flush";
    } else if (score == 8) {
        return "Four of a Kind";
    } else if (score == 7) {
        return ("Full House");
    } else if (score == 6) {
        return "Flush";
    } else if (score == 5) {
        return "Straight";
    } else if (score == 4){ 
        return "Three of a Kind";
    } else if (score == 3) {
        return "Two Pair";
    } else if (score == 3) {
        return "One Pair";
    } else {
        return "High Card";
    }
    }

void Game::compareHands() {
    map<string, int> playerScores;
    for (int playerIndex = 0; playerIndex < 5; playerIndex++) {
        Player currentPlayer = players.front();
        players.pop();

        vector<Card> playerCards;
        for (int cardIndex = 0; cardIndex < 7; cardIndex++) {
            playerCards.push_back(combinedHand[playerIndex][cardIndex]);
        }
        Hand playerHand(playerCards);
        int score = playerHand.calculateBestHandScore();
        playerScores[currentPlayer.getName()] = score;
    }
    string bestHandPlayerName;
    int bestScore = -1;
    for(auto& score : playerScores) {
        if (score.second > bestScore) {
            bestScore = score.second;
            bestHandPlayerName = score.first;
        }
    
    }
    string bestHandString = mapScoreToHand(bestScore);

    cout << "Winner: " << bestHandPlayerName << " with a " << bestHandString << endl; // I want to take the score and match it to the actual hand...also display everyone's hand...

    for(auto& score : playerScores) {
        string playerName = score.first;
        int playerScore = score.second;
        string playerHandString = mapScoreToHand(playerScore);

        cout << playerName << " had a " << playerHandString << "." << endl;
    }
}






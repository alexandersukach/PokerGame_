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
        string computerName = "CPU " + to_string(i + 1);
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



// Simply for display purposes....instead of displaying the
// hand's score, display the actual name for that hand. 
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






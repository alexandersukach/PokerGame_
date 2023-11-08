#include "Game.h"
#include <vector>
#include <string>
#include <iostream>
#include "string.h"
#include "Player.h"

#include <string>
using namespace std;



    Game::Game(const string& userName, double userStartingBalance) : gameDeck() {
    initializePlayers(userName, userStartingBalance);
}

    
    void Game::initializePlayers(const string& userName, double playerBalance){
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


void Game::dealHoleCards() {
    for (int cardIndex = 0; cardIndex < 2; cardIndex++) {
        for (int playerIndex = 0; playerIndex < 5; playerIndex++) {
            Player& player = players.front(); 
            playerHoleCards[playerIndex][cardIndex] = gameDeck.dealCard();
            players.push(player);
            players.pop();
        }
    }
}
        // BETTING ROUND 1

    // Dealing community cards 
        
    void Game::dealFlop() {
        gameDeck.burnCard();
        for (int i = 0; i < 3; i++) {
            Card dealtCard = gameDeck.dealCard();
            communityCards[i] = dealtCard;
        }
    }
        // BETTING ROUND 2
    void Game::dealTurn() {
        gameDeck.burnCard();
        Card dealtCard = gameDeck.dealCard();
        communityCards[3] = dealtCard;
    }
        // BETTING ROUND 3
    void Game::dealRiver() {
        gameDeck.burnCard();
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


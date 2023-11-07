#include "Game.h"
#include <vector>
#include <string>
#include <iostream>
#include "string.h"
#include "Player.h"


class Game {
    private:
    Card communityCards[5]; // Max 5
    Card playerHoleCards[5][2]; // Two cards per player, maximum 5 players
    /*
    I could just set it 5 (max number players) and deal the cards while the first argument hasn't reached 5*/
    Card combinedHands[5][7]; // Should i Just make them all empty
    std::queue<Player> players;
    Deck gameDeck;
    Player userPlayer;
    
    public:
    Game(const std::string& userName, int userStartingBalance) : gameDeck() {
        initializePlayers(userName, userStartingBalance);
    }

    void initializePlayers(const std::string& userName, int userStartingBalance) {
        userPlayer = Player(userName, userStartingBalance);
        const int numComputerPlayers = 4; 
        players.push(userPlayer);

        for (int i = 0; i < numComputerPlayers; i++) {
            std::string computerName = "Computer Player " + std::to_string(i + 1);
            int startingBalance = rand() % 1000 + 1000; // Random starting balance
            players.push(Player(computerName, startingBalance));
        }
    }


void dealHoleCards() {
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
        
    void dealFlop() {
        gameDeck.burnCard();
        for (int i = 0; i < 3; i++) {
            Card dealtCard = gameDeck.dealCard();
            communityCards[i] = dealtCard;
        }
    }
        // BETTING ROUND 2
    void dealTurn() {
        gameDeck.burnCard();
        Card dealtCard = gameDeck.dealCard();
        communityCards[3] = dealtCard;
    }
        // BETTING ROUND 3
    void dealRiver() {
        gameDeck.burnCard();
        Card dealtCard = gameDeck.dealCard();
        communityCards[4] = dealtCard;
    }
        // BETTING ROUND 4
    // Combining community cards and each player's cards to compare hand strength

void combineHands() {
    for (int playerIndex = 0; playerIndex < players.size(); playerIndex++) {

        for (int i = 0; i < 2; i++) {
            combinedHands[playerIndex][i] = playerHoleCards[playerIndex][i];
        }

        for (int i = 2; i < 7; i++) {
            combinedHands[playerIndex][i] = communityCards[i - 2];
        }
    }
}

    // Moving min elemetn to front?

void selectionSortCombinedHands(int playerIndex) {
        for (int i = 0; i < 6; i++) {
            int minIndex = i;
            for(int j = 1; j < 7; j++) {
                int rank1 = combinedHands[playerIndex][minIndex].getRank();
                int rank2 = combinedHands[playerIndex][j].getRank();

                if (rank1 > rank2) {
                    minIndex = j;
                }
            }
            if (minIndex != i) {
                std::swap(combinedHands[playerIndex][i], combinedHands[playerIndex][minIndex]);
            }
            
        }
    }



};
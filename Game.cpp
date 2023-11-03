#include "Game.h"
#include <vector>

Game::Game() : gameDeck() {}

// initializePlayers

void Game::dealHoleCards() {
        for(Player& player : players) {
            for (int cardIndex = 0; cardIndex < 2; cardIndex++) {
                for (int playerIndex = 0; playerIndex < players.size(); playerIndex++) {
                    playerHoleCards[playerIndex][cardIndex] = gameDeck.dealCard();
                }
            }
        }
}
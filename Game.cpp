#include "Game.h"
#include "BettingRound.h"
#include "Card.h"
#include "Deck.h"
#include "DoublyLinkedList.h"
#include "Hand.h"
#include "Player.h"
#include "string.h"
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>
using namespace std;

Game::Game(const string &userName, double userStartingBalance) : gameDeck() {
  initializePlayers(userName, userStartingBalance);
}
int Game::findPlayerIndex(const Player &player) const {
  int index = 0;
  std::queue<Player> tempPlayers = players;

  while (!tempPlayers.empty()) {
    if (tempPlayers.front() == player) {
      return index;
    }
    tempPlayers.pop();
    index++;
  }
  // Player not found, return an invalid index or handle it appropriately
  return -1;
}

Player Game::getUserPlayer() const { return userPlayer; }
void Game::displayPlayerHand(const Player &player) const {
  cout << "\nYour hand: " << endl;
  int userIndex = findPlayerIndex(player);
  cout << playerHoleCards[userIndex][0].toString() << ", ";
  cout << playerHoleCards[userIndex][1].toString();
  cout << endl;
}

void Game::displayCommunityFlop() {
  cout << "Community cards:" << endl;
  cout << communityCards[0].toString() << ", ";
  cout << communityCards[1].toString() << ", ";
  cout << communityCards[2].toString() << endl;
  cout << endl;
}

void Game::displayCommunityTurn() {
  cout << "Community cards:" << endl;
  cout << communityCards[0].toString() << ", ";
  cout << communityCards[1].toString() << ", ";
  cout << communityCards[2].toString() << ", ";
  cout << communityCards[3].toString() << endl;
  cout << endl;
}

void Game::displayCommunityRiver() {
  cout << "Community cards:" << endl;
  cout << communityCards[0].toString() << ", ";
  cout << communityCards[1].toString() << ", ";
  cout << communityCards[2].toString() << ", ";
  cout << communityCards[3].toString() << ", ";
  cout << communityCards[4].toString() << endl;
  cout << endl;
}

/*
void Game::displayCommunityCards() {
    cout << "Community Cards: ";
    for (const Card& card : communityCards) {
        cout << card.toString() << ", ";
    }
    cout << endl;
}*/

void Game::printPlayersNames() {
  cout << "\nPlayers in the game:" << endl;
  queue<Player> tempPlayers = players;
  while (!tempPlayers.empty()) {
    cout << tempPlayers.front().getName();
    if (tempPlayers.size() > 1) {
      cout << ", ";
    } else {
      cout << ". " << endl;
    }
    tempPlayers.pop();
  }
}
void Game::initializePlayers(const string &userName, double playerBalance) {
  // Use the member variable directly, not a local variable
  userPlayer = Player(userName, playerBalance, false);

  const int numComputerPlayers = 4;
  players.push(userPlayer);

  for (int i = 0; i < numComputerPlayers; i++) {
    string computerName = "CPU " + to_string(i + 1);
    players.push(Player(computerName, playerBalance,
                        true)); // Computer players are marked as such
  }
  // Set the initial dealer
  dealer = &players.front();
}

bool Game::isOver() const { return userPlayer.getBalance() == 0; }

void Game::updateActivePlayers(queue<Player> &active) {
  // there's a pretty big bug here- the parameter and class member have the same
  // name, so the activePlayers = true line at the end of the functions does not
  // update the class activePlayers but instead the local activePlayers (so this
  // funciton ends up having no effect); then later in the code, you get a seg
  // fault because you're using an empty activePlayers list.
  queue<Player> temp;
  while (!active.empty()) {
    Player currentPlayer = active.front();
    active.pop();
    if (!currentPlayer.hasFolded()) {
      temp.push(currentPlayer);
    }
  }
  activePlayers = temp;
}

std::queue<Player> Game::getActivePlayers() const { return activePlayers; }
void Game::dealHoleCards() {

  for (int playerIndex = 0; playerIndex < 5; playerIndex++) {
    playerHoleCards[playerIndex][0] = gameDeck.dealCard();
  }

  for (int playerIndex = 0; playerIndex < 5; playerIndex++) {
    playerHoleCards[playerIndex][1] = gameDeck.dealCard();
  }
}

// BETTING ROUND 1

void Game::dealFlop(Deck &roundDeck) {
  roundDeck.burnCard();
  for (int i = 0; i < 3; i++) {
    Card dealtCard = gameDeck.dealCard();
    communityCards[i] = dealtCard;
  }
}
// BETTING ROUND 2
void Game::dealTurn(Deck &roundDeck) {
  roundDeck.burnCard();
  Card dealtCard = gameDeck.dealCard();
  communityCards[3] = dealtCard;
}
// BETTING ROUND 3
void Game::dealRiver(Deck &roundDeck) {
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
  } else if (score == 4) {
    return "Three of a Kind";
  } else if (score == 3) {
    return "Two Pair";
  } else if (score == 2) {
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
  for (auto &score : playerScores) {
    if (score.second > bestScore) {
      bestScore = score.second;
      bestHandPlayerName = score.first;
    }
  }
  string bestHandString = mapScoreToHand(bestScore);

  cout << "Winner: " << bestHandPlayerName << " with a " << bestHandString
       << endl; // I want to take the score and match it to the actual
                // hand...also display everyone's hand...

  for (auto &score : playerScores) {
    string playerName = score.first;
    int playerScore = score.second;
    string playerHandString = mapScoreToHand(playerScore);

    cout << playerName << " had a " << playerHandString << "." << endl;
  }
}

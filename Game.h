/*
 *  Declaration of the Game class.
 */

#ifndef GAME_H
#define GAME_H

#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include <queue>
#include <string>

using namespace std;

class Game {
public:
  Game(const string &userName, int userStartingBalance);
  const queue<Player> &getPlayers() const { return players; }
  void initializePlayers(const string &userName, int playerBalance);
  void dealHoleCards();
  void dealFlop(Deck &roundDeck);
  void dealTurn(Deck &roundDeck);
  void dealRiver(Deck &roundDeck);
  void combineHands();
  void compareHands();
  string mapScoreToHand(int score);
  void printPlayersNames();
  bool isOver() const;
  void updateActivePlayers();
  // void displayPlayerHoleCards(const Player &player) const;
  void displayAllPlayerHoleCards() const;
  int findPlayerIndex(const Player &player) const;
  Player getUserPlayer() const;
  queue<Player> getActivePlayers() const;
  void displayCommunityFlop();
  void displayCommunityTurn();
  void displayCommunityRiver();
  void startNextRound();
  void printPlayerOrder() const;

private:
  Player userPlayer;
  Player *dealer;
  Card communityCards[5];
  Card playerHoleCards[5][2];
  Card combinedHand[5][7];
  Deck gameDeck;
  queue<Player> activePlayers;
  queue<Player> players;
};

#endif // GAME_H
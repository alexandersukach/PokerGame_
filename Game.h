#ifndef GAME_H
#define GAME_H
#include "Card.h"
#include "Deck.h"
#include "Player.h" // Include any other necessary headers here
#include <queue>
#include <string>

using namespace std;

class Game {
public:
  Game(const string &userName, double userStartingBalance);
  void initializePlayers(const string &userName, double playerBalance);
  // void dealHoleCards(queue<Player> &activePlayers, Deck &roundDeck);
  void dealHoleCards();
  void dealFlop(Deck &roundDeck);
  void dealTurn(Deck &roundDeck);
  void dealRiver(Deck &roundDeck);
  void combineHands();
  void compareHands();
  string mapScoreToHand(int score);
  void printPlayersNames();
  bool isOver() const;
  void updateActivePlayers(queue<Player> &activePlayers);
  void displayPlayerHand(const Player &player) const;
  int findPlayerIndex(const Player &player) const;
  Player getUserPlayer() const;
  std::queue<Player> getActivePlayers() const;
  void displayCommunityFlop();
  void displayCommunityTurn();
  void displayCommunityRiver();

  queue<Player> players;

  Player *currentPlayer;
  Player userPlayer;
  Player *dealer;
  Card communityCards[5];     // 5 total
  Card playerHoleCards[5][2]; // [playerIndex][card]
  Card combinedHand[5][7];    //[playerIndex][card]
                              // could
  Deck gameDeck;

  // int currentTurn;
  // bool isGameOver = false;
  // bool isHandOver = false;
private:
  std::queue<Player> activePlayers; // Add this line
};

#endif // GAME_H
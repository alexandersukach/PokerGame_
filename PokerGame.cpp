#include "BettingRound.h"
#include "Card.h"
#include "Deck.h"
#include "DoublyLinkedList.h"
#include "Game.h"
#include "Hand.h"
#include "Player.h"
#include "string.h"
#include <iomanip>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

void displayRules() {
  cout << "                 =====================================" << endl;
  cout << "                       Texas Hold'em Poker Rules      " << endl;
  cout << "                 =====================================" << endl;
  cout
      << "- Start by specifying the buy-in amount at the beginning of the game."
      << endl;
  //   cout << "- The game uses standard blinds: $5 for the small blind and $10
  //   for"
  //        << endl;
  //   cout << "  the big blind." << endl;
  //   cout << "  Blinds ensure there is always money in the pot to compete
  //   for."
  //        << endl;
  //   cout << "- The player to the immediate left of the dealer assumes the
  //   role "
  //        << endl;
  //   cout << " of the small blind." << endl;
  //   cout
  //       << "- The player to the left of the small blind takes on the role of
  //       the "
  //       << endl;
  //   cout << "  big blind." << endl;
  cout << "- During each round of betting, players can check, bet, call, "
          "or raise, depending on the current game conditions."
       << endl;
  cout << "- Starting with the small blind and proceeding clockwise, each "
          "player "
       << endl;
  cout << "  receives two 'hole cards' which remain concealed from others."
       << endl;
  cout << "- Players engage in a round of betting based on their hole cards and"
       << endl;
  cout << "  community cards to be revealed." << endl;
  cout << "- A card is then 'burned', or removed from the deck." << endl;
  cout << "- The subsequent three cards are placed face up on the board (the "
          "flop). "
       << endl;
  cout << "- Following the flop, another round of betting ensues." << endl;
  cout << "- A card is then 'burned' and the next card is placed face up (the "
          "turn)."
       << endl;
  cout << "- Another round of betting follows the turn." << endl;
  cout << "- A final card is then 'burned' and (the river) card is drawn "
          "following"
       << endl;
  cout << "  it, which completes the set of community cards." << endl;
  cout << "- The final round of betting takes place, and players try to form "
          "their "
       << endl;
  cout << "  best 5-card hand, utilizing both their 'hole cards' and the "
          "'community "
       << endl;
  cout << "  cards' on the table." << endl;
  cout << "- If players have equal hands, a 'chop pot' occurs." << endl;
}
void displayHandRankings() {
  const int cardWidth = 9;
  const string RED_TEXT = "\033[31m";   // Red text
  const string BLACK_TEXT = "\033[30m"; // Black text
  const string RESET_COLOR = "\033[0m"; // Default text
  const string SPADE = "\u2660";        // Unicode for Spade symbol
  const string HEART = "\u2665";        // Unicode for Heart symbol
  const string DIAMOND = "\u2666";      // Unicode for Diamond symbol
  const string CLUB = "\u2663";         // Unicode for Club symbol
  cout << "=================== Hand Rankings ====================" << endl;
  cout << "                (Strongest to weakest)" << endl;
  cout << "Royal Flush:"
       << "       " << BLACK_TEXT << left << setw(cardWidth) << (" A " + SPADE)
       << left << setw(cardWidth) << (" K " + SPADE) << left << setw(cardWidth)
       << (" Q " + SPADE) << left << setw(cardWidth) << (" J " + SPADE) << left
       << setw(cardWidth) << ("10 " + SPADE) << RESET_COLOR << endl;
  cout << "Straight Flush:"
       << "    " << RED_TEXT << left << setw(cardWidth) << (" 8 " + HEART)
       << left << setw(cardWidth) << (" 7 " + HEART) << left << setw(cardWidth)
       << (" 6 " + HEART) << left << setw(cardWidth) << (" 5 " + HEART) << left
       << setw(cardWidth) << (" 4 " + HEART) << RESET_COLOR << endl;
  cout << "Four of a Kind:"
       << "    " << BLACK_TEXT << left << setw(cardWidth) << (" 7 " + CLUB)
       << RESET_COLOR << RED_TEXT << left << setw(cardWidth)
       << (" 7 " + DIAMOND) << RESET_COLOR << BLACK_TEXT << left
       << setw(cardWidth) << (" 7 " + SPADE) << RESET_COLOR << RED_TEXT << left
       << setw(cardWidth) << (" 7 " + HEART) << RESET_COLOR << BLACK_TEXT
       << left << setw(cardWidth) << (" 3 " + CLUB) << RESET_COLOR << endl;
  cout << "Full House:"
       << "        " << RED_TEXT << left << setw(cardWidth) << (" Q " + HEART)
       << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << (" Q " + CLUB)
       << left << setw(cardWidth) << (" Q " + SPADE) << left << setw(cardWidth)
       << (" 4 " + SPADE) << RESET_COLOR << RED_TEXT << left << setw(cardWidth)
       << (" 4 " + HEART) << RESET_COLOR << endl;
  cout << "Flush:"
       << "             " << BLACK_TEXT << left << setw(cardWidth)
       << (" 4 " + CLUB) << left << setw(cardWidth) << (" J " + SPADE) << left
       << setw(cardWidth) << (" A " + SPADE) << left << setw(cardWidth)
       << (" 7 " + CLUB) << left << setw(cardWidth) << (" 9 " + CLUB)
       << RESET_COLOR << endl;
  cout << "Straight:"
       << "          " << BLACK_TEXT << left << setw(cardWidth)
       << (" Q " + CLUB) << RESET_COLOR << RED_TEXT << left << setw(cardWidth)
       << (" J " + DIAMOND) << left << setw(cardWidth) << ("10 " + HEART)
       << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << (" 9 " + CLUB)
       << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << (" 3 " + HEART)
       << RESET_COLOR << endl;
  cout << "Three of a Kind:"
       << "   " << RED_TEXT << left << setw(cardWidth) << (" K " + HEART)
       << left << setw(cardWidth) << (" K " + DIAMOND) << RESET_COLOR
       << BLACK_TEXT << left << setw(cardWidth) << (" K " + SPADE)
       << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << ("10 " + HEART)
       << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth)
       << (" 7 " + SPADE) << RESET_COLOR << endl;
  cout << "Two Pair:"
       << "          " << BLACK_TEXT << left << setw(cardWidth)
       << (" 8 " + SPADE) << RESET_COLOR << RED_TEXT << left << setw(cardWidth)
       << (" 8 " + HEART) << RESET_COLOR << BLACK_TEXT << left
       << setw(cardWidth) << (" 5 " + SPADE) << left << setw(cardWidth)
       << (" 5 " + CLUB) << RESET_COLOR << RED_TEXT << left << setw(cardWidth)
       << (" 3 " + HEART) << RESET_COLOR << endl;
  cout << "One Pair:"
       << "          " << BLACK_TEXT << left << setw(cardWidth)
       << ("10 " + CLUB) << left << setw(cardWidth) << ("10 " + SPADE) << left
       << setw(cardWidth) << (" 7 " + CLUB) << RESET_COLOR << RED_TEXT << left
       << setw(cardWidth) << (" 4 " + HEART) << RESET_COLOR << BLACK_TEXT
       << left << setw(cardWidth) << (" 2 " + CLUB) << RESET_COLOR << endl;
  cout << "High Card:"
       << "         " << RED_TEXT << left << setw(cardWidth) << (" A " + HEART)
       << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << (" Q " + CLUB)
       << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << ("10 " + HEART)
       << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << (" 7 " + CLUB)
       << RESET_COLOR << RED_TEXT << left << setw(cardWidth)
       << (" 4 " + DIAMOND) << RESET_COLOR << endl;
  cout << "======================================================" << endl;
}

int main() {
  displayRules();
  displayHandRankings();

  cout << "What is your name? ";
  string userName;
  cin >> userName;

  cout << "How much would you like to buy in for, " << userName << "? ";

  double buyInAmount;
  cin >> buyInAmount;
  double minBet = 10.00;
  Game pokerGame(userName, buyInAmount);
  // pokerGame.initializePlayers();
  pokerGame.printPlayersNames();

  Deck gameDeck = Deck();
  //   gameDeck.print();
  queue<Player> playersStillIn;

  pokerGame.dealHoleCards();
  pokerGame.displayPlayerHand(pokerGame.getUserPlayer());

  BettingRound preFlop(pokerGame.players, minBet);
  preFlop.playRound();
  cout << "Total pot: " << preFlop.getPot() << endl;
  pokerGame.dealFlop(gameDeck);
  pokerGame.displayCommunityFlop();
  pokerGame.updateActivePlayers(pokerGame.players);

  playersStillIn = pokerGame.players;
  /*
    for (Player player: playersStillIn) {
       player.resetBet();
    }
  */

  BettingRound preTurn(pokerGame.getActivePlayers(), minBet);
  preTurn.playRound();
  cout << "Total pot: " << preTurn.getPot() << endl;
  pokerGame.dealTurn(gameDeck);
  pokerGame.displayCommunityTurn();
  pokerGame.updateActivePlayers(pokerGame.players);

  BettingRound preRiver(pokerGame.getActivePlayers(), minBet);
  preRiver.playRound();
  cout << "Total pot: " << preRiver.getPot() << endl;
  pokerGame.dealRiver(gameDeck);
  pokerGame.displayCommunityRiver();
  pokerGame.updateActivePlayers(pokerGame.players);

  return 0;
}

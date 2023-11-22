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
    const int cardWidth = 9;
    const string RED_TEXT = "\033[31m"; // Red text
    const string BLACK_TEXT = "\033[30m"; // Black text 
    const string RESET_COLOR = "\033[0m"; // Default text
    const string SPADE = "\u2660";   // Unicode for Spade symbol
    const string HEART = "\u2665";   // Unicode for Heart symbol
    const string DIAMOND = "\u2666"; // Unicode for Diamond symbol
    const string CLUB = "\u2663";    // Unicode for Club symbol
    cout << "=================== Hand Rankings ====================" << endl;
    cout << "                (Strongest to weakest)" << endl;
    cout << "Royal Flush:" << "       " << BLACK_TEXT << left << setw(cardWidth) << (" A " + SPADE) << left << setw(cardWidth) << (" K " + SPADE) << left << setw(cardWidth) << (" Q " + SPADE) << left << setw(cardWidth) << (" J " + SPADE) << left << setw(cardWidth) << ("10 " + SPADE) << RESET_COLOR << endl;
    cout << "Straight Flush:" << "    " << RED_TEXT << left << setw(cardWidth) << (" 8 " + HEART) << left << setw(cardWidth) << (" 7 " + HEART) << left << setw(cardWidth) << ( " 6 " + HEART) << left << setw(cardWidth) << (" 5 " + HEART) << left << setw(cardWidth) << (" 4 " + HEART) << RESET_COLOR << endl;
    cout << "Four of a Kind:" << "    " << BLACK_TEXT << left << setw(cardWidth) << (" 7 " + CLUB) << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << (" 7 " + DIAMOND) << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << (" 7 " + SPADE) << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << (" 7 " + HEART) << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << (" 3 " + CLUB) << RESET_COLOR << endl;
    cout << "Full House:" << "        " << RED_TEXT << left << setw(cardWidth) << (" Q " + HEART) << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << (" Q " + CLUB) << left << setw(cardWidth) << (" Q " + SPADE) << left << setw(cardWidth) << (" 4 " + SPADE) << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << (" 4 " + HEART)<< RESET_COLOR << endl;
    cout << "Flush:" << "             " << BLACK_TEXT << left << setw(cardWidth) << (" 4 " + CLUB) << left << setw(cardWidth) << (" J " + SPADE) << left << setw(cardWidth) << (" A " + SPADE) << left << setw(cardWidth) << (" 7 " + CLUB) << left << setw(cardWidth) << (" 9 " + CLUB) << RESET_COLOR << endl;
    cout << "Straight:" << "          " << BLACK_TEXT << left << setw(cardWidth) << (" Q " + CLUB) << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << (" J " + DIAMOND) << left << setw(cardWidth) << ("10 " + HEART) << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << (" 9 " + CLUB) << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << (" 3 " + HEART) << RESET_COLOR << endl;
    cout << "Three of a Kind:" << "   " << RED_TEXT << left << setw(cardWidth) << (" K " + HEART) << left << setw(cardWidth) << (" K " + DIAMOND) << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << (" K " + SPADE) << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << ("10 " + HEART) << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << (" 7 " + SPADE) << RESET_COLOR << endl;
    cout << "Two Pair:" << "          " << BLACK_TEXT << left << setw(cardWidth) << (" 8 " + SPADE) << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << (" 8 " + HEART) << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << (" 5 " + SPADE) << left << setw(cardWidth) << (" 5 " + CLUB) << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << (" 3 " + HEART) << RESET_COLOR << endl;
    cout << "One Pair:" << "          " << BLACK_TEXT << left << setw(cardWidth) << ("10 " + CLUB) << left << setw(cardWidth) << ("10 " + SPADE) << left << setw(cardWidth) << (" 7 " + CLUB) << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << (" 4 " + HEART) << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << (" 2 " + CLUB) << RESET_COLOR << endl;
    cout << "High Card:" << "         " << RED_TEXT << left << setw(cardWidth) << (" A " + HEART) << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << (" Q " + CLUB) << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << ("10 " + HEART) << RESET_COLOR << BLACK_TEXT << left << setw(cardWidth) << (" 7 " + CLUB) << RESET_COLOR << RED_TEXT << left << setw(cardWidth) << (" 4 " + DIAMOND) << RESET_COLOR << endl;
    cout << "======================================================" << endl;
}


int main() {
    displayRules();
    displayHandRankings();

    cout << "What is your name? ";
    string userName;
    cin >> userName;

    cout << "How much would you like to buy in for? ";
    
    double buyInAmount;
    cin >> buyInAmount;
    double minBet = 10.00;
    Game pokerGame(userName, buyInAmount);
    //pokerGame.initializePlayers();
    pokerGame.printPlayersNames();


    Deck gameDeck = Deck();

    pokerGame.dealHoleCards(pokerGame.players, gameDeck);
    pokerGame.displayPlayerHand(pokerGame.getUserPlayer());
    BettingRound preFlop(pokerGame.players, minBet);
    preFlop.playRound();

    return 0; 
}
    /*
        
    preFlop.playRound();
    pokerGame.updateActivePlayers(pokerGame.players);*/
/*

    while (!pokerGame.isOver()) {
        Deck gameDeck = Deck();
        
        // Assuming players is the queue of players in your Game class
        pokerGame.dealHoleCards(pokerGame.players, gameDeck);
        BettingRound preFlop(pokerGame.players);
        preFlop.playRound();
        pokerGame.updateActivePlayers(pokerGame.players);

        pokerGame.dealFlop(gameDeck);
        BettingRound postFlop(pokerGame.players);
        postFlop.playRound();
        pokerGame.updateActivePlayers(pokerGame.players);

        pokerGame.dealTurn(gameDeck);
        BettingRound postTurn(pokerGame.players);
        postTurn.playRound();
        pokerGame.updateActivePlayers(pokerGame.players);

        pokerGame.dealRiver(gameDeck);
        BettingRound postRiver(pokerGame.players);
        postRiver.playRound();
        pokerGame.updateActivePlayers(pokerGame.players);
    }*/
/*
    Game pokerGame(userName, amountToBuyIn);
    pokerGame.initializePlayers(userName, amountToBuyIn);
    // When I run the program, after inputting the ammountToBuyIn, i receive a segmentation fault: 11 error, why could that be?
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
      // If user balance hits 0, game over

        // Reset everything here...
        // Reset deck, reset queue of players to what is was (long so they're still in the game)
        // reset rounds...etc

    }
}






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
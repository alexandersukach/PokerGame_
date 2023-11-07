#include <queue>
#include "Player.h"
#include <iostream>
using namespace std;
class Round {
    private:
        //int bettingRound;
        queue<Player> players;
        int pot;
        int currentRoundBet;
        bool isBetMade;
        bool isRaiseMade;
        bool isReRaiseMade;
        int initialBet = 10; // currentRoundBet is bigBlind maybe

    public:

    Round(int number, queue<Player>& roundPlayers) {
        //bettingRound = number;
        players = roundPlayers;
        pot = 0;
        currentRoundBet = 10;
        isBetMade = false;
        isRaiseMade = false;
        isReRaiseMade = false;
    }


    void playRound() {

        if(isBetMade) {
            void handleBetMadeActions();
        } else {
            void handleNoBetActions();
        }

        if(isRaiseMade) {
            void handleRaiseMadeActions();
        } else {
            void handleNoRaiseActions();
        }
        if(isReRaiseMade) {
            void handleReRaiseMadeActions();
            } else {
            void handleNoReRaiseActions();
        }
        // so could i just make a fold method to use
        // for the elses

    }

    void initialBetAmount(int initialRoundBet) {
        currentRoundBet = initialRoundBet;


    }



    void handleBetMadePlayerActions() {
        char choiceBet;
        cout << "Would you like to (c)all, (r)aise, or (f)old?";
        cin >> choiceBet;
        choiceBet = tolower(choiceBet);

        switch(choiceBet) {
            case 'f':
                players.front().fold();
                // Remove a player here, without affecting outer queue to not
                // have to initialize players again...does for loop handle it...idk
                break;
            case 'c':
                int amountToCall = currentRoundBet - players.front().getCurrentBet();
                players.front().placeBet(amountToCall);
                players.front().setCurrentBet(currentRoundBet);
                break;
            case 'r':
                int raiseAmount;
                cout << "Enter raise amount: ";
                cin >> raiseAmount;

                if (raiseAmount <= players.front().getBalance()) {
                    if(raiseAmount == players.front().getBalance()) {
                        cout << "All in";
                    }
                    players.front().placeBet(raiseAmount);
                    players.front().setCurrentBet(currentRoundBet + raiseAmount);
                }
                break;
            default:
                cout << "Choose a valid option";

        }
    }

    void handleNoBetPlayerActions() {
        char choiceNoBet;
        cout << "Would you like to (b)et or (c)heck? ";
        cin >> choiceNoBet;
        choiceNoBet = tolower(choiceNoBet);

        switch(choiceNoBet) {
            case 'b':
                int betAmount;
                cout << "Enter the bet amount: ";
                cin >> betAmount;
                // Add logic to ensure the bet amount is valid and within the player's balance
                if (betAmount > 0 && betAmount <= players.front().getBalance()) {
                    players.front().placeBet(betAmount);
                    players.front().setCurrentBet(betAmount);
                    currentRoundBet = betAmount;
                    isBetMade = true;
                }
                break;
            case 'c':
                // need check method that just goes to next player
                // I should just have one method that asks for bet...okay i see ..

        }
    }

    void handleCPUPlayerActions() {
        // is this something i need... recommendation popped up: cpuPlayers[0].makeDecision();
        // probabilities set. later adjusted given game scenario / player balance
        double betProbability = 0.3;
        double callProbability = 0.0;
        double foldProbability = 0.0;

        bool isRaiseMade = false;          // somehow cover that a raise is made 
        if (isRaiseMade) {
            betProbability = 0.0; // Only options are to call or fold
            callProbability = 0.6;
            foldProbability = 0.4;
        }

        


    }
    
    void handleNoBetYetPlayerActions(Player& player) {
        cout << "Would you like to (b)et or (c)all? " ;
        char choice;
        cin >> choice;
        choice = tolower(choice);

        switch(choice) {
            case 'b':
            int betAmount;
                cout << "How much would you like to bet? ";
                cin  >> betAmount;
                if (betAmount >= 2 * initialBet && betAmount <= player.getBalance()) {
                    player.placeBet(betAmount);
                    player.setBalance(player.getBalance() - betAmount);
                    currentRoundBet = betAmount;
                    isBetMade = true;
                    pot += betAmount;
                } else {
                    cout << "Check that bet is at least twice the current bet and within your budget..." << endl;

                }
                break;
            case 'c'
        }
        }
};
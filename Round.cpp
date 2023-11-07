#include <queue>
#include "Player.h"
#include <iostream>
using namespace std;
class Round {
    private:
        //int bettingRound;
        queue<Player> players;
        double pot;
        double currentRoundBet;
        bool isBetMade;
        bool isRaiseMade;
        double initialBet = 10.00; // currentRoundBet is bigBlind maybe

    public:

    Round(int number, queue<Player>& roundPlayers) {
        //bettingRound = number;
        players = roundPlayers;
        pot = 0.00;
        currentRoundBet = 10.00;
        isBetMade = false;
        isRaiseMade = false;
    }



void handleNoBetYetPlayerActions(Player& player) {
    cout << "Would you like to (b)et or (c)heck " ;
    char choice;
    cin >> choice;
    choice = tolower(choice);

    switch (choice) {
        case 'b':
            double betAmount;
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
        case 'c':
            cout << "You check, next player" << endl;
            break;
        default:
            cout << "Invalid action. Try again" << endl;
    }
} // Missing closing bracket here


void handleBetPlayerActions(Player& player) {
            cout << "Would you like to (c)all, (f)old, or (r)aise? " << endl;
            char choice;
            cin >> choice;
            choice = tolower(choice);
            switch(choice) {
                case 'c':
                    //call // i need to keep track of current bet

                    double amountToCall = currentRoundBet - player.getCurrentBet(); 
                    if(amountToCall >= player.getBalance()) {
                        cout << "You're forced to go all in!" << endl;
                        player.placeBet(player.getBalance());
                    } else {
                        cout << "You call, next player" << endl;
                        player.placeBet(amountToCall);
                    }    
                    pot += amountToCall;
                    break;
                case 'f':
                    player.fold();
                    break;
                case 'r':
                    double raiseAmount;
                    cout << "How much would you like to raise by? ";
                    cin  >> raiseAmount;
                    if (raiseAmount > player.getBalance()) {
                        cout << "Not enough money." << endl;
                    } else {
                        player.placeBet(raiseAmount);
                        pot += raiseAmount;
                    }
                    break;
                default:
                    cout << "Invalid action" << endl;
            }
        }
    void handleRaisePlayerActions(Player& player) {
        cout << "Would you like to (c)all or (f)old? " << endl;
            char choice;
            cin >> choice;
            choice = tolower(choice);
            switch(choice) {
                case 'c':

                    double amountToCall = currentRoundBet - player.getCurrentBet(); 
                    if(amountToCall >= player.getBalance()) {
                        cout << "You're forced to go all in!" << endl;
                        player.placeBet(player.getBalance());
                    } else {
                        cout << "You call, next player" << endl;
                        player.placeBet(amountToCall);
                    }    
                    pot += amountToCall;
                    break;
                case 'f':
                    player.fold();
                    break;
                default:
                    cout << "Invalid action" << endl;
            }
                    
    }


void handleCpuActions(Player& computerPlayer) {
    double randomValue = static_cast<double>(rand()) / RAND_MAX;

    if (isBetMade) {
        double callProbability = 0.4;
        double foldProbability = 0.3;

        if (randomValue < callProbability) {
            // CPU calls
            double amountToCall = currentRoundBet - computerPlayer.getCurrentBet();
            computerPlayer.placeBet(amountToCall);
            pot += amountToCall;
        } else if (randomValue < callProbability + foldProbability) {
            // CPU folds
            computerPlayer.fold();
        } else {
            // CPU raises in response to the human player's bet
            double maxRaiseAmount = computerPlayer.getBalance() - computerPlayer.getCurrentBet();
            double minRaiseAmount = 2 * currentRoundBet;
            int possibleRaise = maxRaiseAmount - minRaiseAmount;

            if (possibleRaise > 0) {
                int raiseAmount = minRaiseAmount + rand() % (possibleRaise + 1);

                if (raiseAmount >= 2 * currentRoundBet) {
                    computerPlayer.placeBet(raiseAmount);
                    pot += raiseAmount;
                    isRaiseMade = true;
                }
            }
        }
    } else { // No bet made by human
        double betProbability = 0.3;
        double checkProbability = 0.5;

        if (randomValue < betProbability) {
            double maxBetAmount = computerPlayer.getBalance();
            double minBetAmount = 2 * currentRoundBet;
            int possibleBet = maxBetAmount - minBetAmount;
            int betAmount = rand() % (possibleBet + 1) + minBetAmount;

            if (betAmount) {
                computerPlayer.placeBet(betAmount);
                pot += betAmount;
                isBetMade = true;
            }
        } else {
            cout << "CPU has checked" << endl;
        }
    }
}


};


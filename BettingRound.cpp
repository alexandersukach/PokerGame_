#include "Player.h"
#include <queue> 
#include <iostream>
#include <cstdlib>
#include "BettingRound.h"

using namespace std;

void BettingRound::playRound() {
    while (!players.empty()) {
        Player& player = players.front(); // Here this would be the small blind right?
        // should it be head - small blind; head->next - big blind

        if (!player.isComputer()) {
            if (isBetMade) {
                handleBetMadePlayerActions(player); // user 
            } else if (isRaiseMade) {
                handleRaiseMadePlayerActions(player); // user
            } else {
                handleNoBetMadePlayerActions(player);
            }
        } else {
            handleCPUActions(player);
        }
        players.push(player);
        players.pop();

        /*
        if (isBetMade || isRaiseMade) {
            isBetMade = false;
            isRaiseMade = false;
            break;
        }
        I would like to make note of first person so once theyr'e reached with no bet or raise,
        // the next cards are shown and the next round goes on
        // I also want that marker to reset anytime someone places the bet*/
        // initiateAction flag
        
    }
}
// Ultimately, it would be nice for the 'someones' to be the player's names...
void BettingRound::handleNoBetMadePlayerActions(Player& user) {
    cout << "Action to you. Would you like to (b)et or (c)heck?" << endl;
    char action;
    cin >> action;
    action = tolower(action);

    switch(action) {
        case 'b':
            cout << "\n How much would you like to bet? ";
            double betAmount;
            cin >> betAmount;
            if (betAmount >= 2 * minRoundBet && betAmount <= user.getBalance()) {
                user.placeBet(betAmount);
                isBetMade = true;
                currentRoundBet = betAmount;
                pot += betAmount;
            } else {
                cout << "\nBet must be at least twice the minimum and within your budget" << endl;
            }
            break;
        case 'c':
            cout << "\nYou check. Action passed to next player" << endl;
            break;
        default:
            cout << "\nInvalid choice. Try again." << endl;
    }

}

void BettingRound::handleBetMadePlayerActions(Player& user) {
    cout << "CPU has placed a bet. Would you like to (c)all, (f)old, or (r)aise? ";
    char action;
    cin >> action;
    action = tolower(action);
    double amountToCall = (currentRoundBet - user.getCurrentBet());

    switch(action) {
        case 'c':
            if (amountToCall >= user.getBalance()) {
                cout << "You're forced to go all in!" << endl;
                user.placeBet(user.getBalance());
                pot += user.getBalance();
            } else {
                cout << "You call, next player..." << endl;
                user.placeBet(amountToCall);
                pot += amountToCall;
            }
            break;
        case 'f':
            cout << "You folded your hand." << endl;
            user.fold();
            break;
        case 'r':
            cout << "\nHow much would you like to raise by?" ;
            double raiseAmount;
            cin >> raiseAmount;
            if (raiseAmount == user.getBalance()) {
                cout << "You're going all-in!";
                user.placeBet(user.getBalance());
            }
            if (raiseAmount >= 2 * minRoundBet && raiseAmount < user.getBalance()) {
                cout << "You raised by " << raiseAmount << ", next player..." << endl;
                user.placeBet(raiseAmount);
                isRaiseMade = true;
                currentRoundBet += raiseAmount;
                pot += raiseAmount;
            } else {
                cout << "\nRaise must be at least twice the initial bet and within your budget.";
            }
            break;
        default:
            cout << "\nInvalid action. Try again." << endl;
    }
}

void BettingRound::handleRaiseMadePlayerActions(Player& user) {
    cout << "Someone raised. Would you like to (c)all or (f)old?";
    char action;
    cin >> action;
    action = tolower(action);
    double amountToCall = currentRoundBet - user.getCurrentBet();

    switch(action) {
        case 'c':
            if (amountToCall >= user.getBalance()) {
                cout << "You're forced to go all in!" << endl;
                user.placeBet(user.getBalance());
                pot += user.getBalance();
            } else {
                cout << "You call, next player..." << endl;
                user.placeBet(amountToCall);
                pot += amountToCall;
            }
            break;
        case 'f':
            cout << "You've folded your hand..." << endl;
            user.fold();
            break;
        default:
            cout << "\nInvalid action. Try again." << endl;
    } 

    }


// players that go all in before the river or turn is dealt 
// are skipped on betting for those rounds....if they lose, remove them from game
// if a player folds, remove them from activePlayer queue before next betting round


/*
I WILL NEED A BETTER SYSTEM FOR THE PROBABILITIES*/

void BettingRound::handleCPUActions(Player& computerPlayer) {
    double randomValue = static_cast<double>(rand()) / RAND_MAX; // generates a value between 0 and 1
    double betProbability;
    double callProbability;
    double foldProbability;
    double raiseProbability;
    double checkProbability; // with check, move onto next person
    // suggestion made by black box?....if (currentRoundBet == 0 && previousRoundWinner != nullptr){
    if (isRaiseMade) {
        callProbability = 0.60;
        //foldProbability = 0.40;
        // We need to ensure the computerPlayer has enough money
        // this prob logic might be wrong...too lazy to fix at the moment...
        if(randomValue < callProbability) {
            double amountToCall = currentRoundBet - computerPlayer.getCurrentBet();
            if (amountToCall >= computerPlayer.getBalance()) {
                // Computer player going all in (do i need any print statements for computer action?)
                computerPlayer.placeBet(computerPlayer.getBalance());
                pot += computerPlayer.getBalance();
            } else {
                computerPlayer.placeBet(amountToCall);
                pot += amountToCall;
            }
        } else {
            computerPlayer.fold(); // Make sure we're taking them out of the activePlayers at the end of the round
        }
    } else if (isBetMade) {
        callProbability = 0.5;
        raiseProbability = 0.3;
        foldProbability = 0.2;

        if (randomValue <= callProbability) {
            double amountToCall = currentRoundBet - computerPlayer.getCurrentBet();
            if (amountToCall >= computerPlayer.getBalance()) {
                // Computer player going all in (do i need any print statements for computer action?)
                computerPlayer.placeBet(computerPlayer.getBalance());
                pot += computerPlayer.getBalance();
            } else {
                computerPlayer.placeBet(amountToCall);
                pot += amountToCall;
            }
        } else if (callProbability <= randomValue <= 0.8) { // raising
            //auto set computer raise to 2 * currentRoundBet;
            double raiseAmount = 2 * currentRoundBet;
            if (raiseAmount >= computerPlayer.getBalance()) {
                // Computer player going all in (do i need any print statements for computer action?)
                computerPlayer.placeBet(computerPlayer.getBalance());
                pot += computerPlayer.getBalance();
            } else {
                computerPlayer.placeBet(raiseAmount);
                pot += raiseAmount;
            }
            isRaiseMade = true;
        }
    } else {
        // I DIDN'T CHECK IF COMPUTER HAS ENOUGH MONEY!!!!!!
        // No bets have been placed yet!
        checkProbability = 0.6;
        betProbability = 0.4;
        if (randomValue <= checkProbability) {
            //player checks, move to next
        } else {
            double betAmount = 2 * currentRoundBet;
            if (betAmount == computerPlayer.getBalance()) {
                computerPlayer.placeBet(computerPlayer.getBalance());
                pot += computerPlayer.getBalance();
            } else  {
                computerPlayer.placeBet(betAmount);
                pot += betAmount;
            }
            }
        }
        isBetMade = true;
    }


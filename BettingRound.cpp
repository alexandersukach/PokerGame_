#include "Player.h"
#include <queue> 
#include <iostream>
#include <cstdlib>
#include "BettingRound.h"

using namespace std;

void BettingRound::playRound() {
    while (!players.empty()) {
        Player& player = players.front();

        if (!player.isComputer()) {
            if (isBetMade) {
                handleBetMadePlayerActions(player);
            } else if (isRaiseMade) {
                handleRaiseMadePlayerActions(player);
            } else {
                handleNoBetMadePlayerActions(player);
            }
        } else {
            handleCPUActions(player);
        }
        players.push(player);
        players.pop();
    }
}

void BettingRound::handleNoBetMadePlayerActions(Player& user) {
    bool validBet = false;

    while (!validBet) {
        cout << "Action to you. Would you like to (b)et or (c)heck?" << endl;
        char action;
        cin >> action;
        action = tolower(action);

        switch(action) {
            case 'b':
                validBet = makeBet(user);
                break;
            case 'c':
                cout << "\nYou check. Action passed to the next player" << endl;
                validBet = true;
                break;
            default:
                cout << "\nInvalid choice. Try again." << endl;
        }
    }
}

bool BettingRound::makeBet(Player& user) {
    cout << "\nHow much would you like to bet? ";
    double betAmount;
    cin >> betAmount;
    
    if (betAmount >= 2 * minRoundBet && betAmount <= user.getBalance()) {
        user.placeBet(betAmount);
        isBetMade = true;
        currentRoundBet = betAmount;
        pot += betAmount;
        return true;
    } else {
        cout << "\nBet must be at least twice the minimum and within your budget" << endl;
        return false;
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

void BettingRound::handleCPUActions(Player& computerPlayer) {
    double randomValue = static_cast<double>(rand()) / RAND_MAX;
    double callProbability;
    double raiseProbability;

    if (isRaiseMade) {
        callProbability = 0.6;
        if (randomValue <= callProbability) {
            double amountToCall = currentRoundBet - computerPlayer.getCurrentBet();
            if (amountToCall >= computerPlayer.getBalance()) {
                computerPlayer.placeBet(computerPlayer.getBalance());
                pot += computerPlayer.getBalance();
            } else {
                computerPlayer.placeBet(amountToCall);
                pot += amountToCall;
            }
        } else {
            computerPlayer.fold();
        }
    } else if (isBetMade) {
        callProbability = 0.5;
        raiseProbability = 0.2;
        if (randomValue <= callProbability) {
            double amountToCall = currentRoundBet - computerPlayer.getCurrentBet();
            if (amountToCall >= computerPlayer.getBalance()) {
                computerPlayer.placeBet(computerPlayer.getBalance());
                pot += computerPlayer.getBalance();
            } else {
                computerPlayer.placeBet(amountToCall);
                pot += amountToCall;
            }
        } else if (randomValue <= (callProbability + raiseProbability)) {
            double raiseAmount = 2 * currentRoundBet;
            if (raiseAmount >= computerPlayer.getBalance()) {
                computerPlayer.placeBet(computerPlayer.getBalance());
                pot += computerPlayer.getBalance();
            } else {
                computerPlayer.placeBet(raiseAmount);
                pot += raiseAmount;
            }
            isRaiseMade = true;
        } else {
            computerPlayer.fold();
        }
    } else {
        callProbability = 0.6;
        if (randomValue <= callProbability) {
            double amountToCall = currentRoundBet - computerPlayer.getCurrentBet();
            if (amountToCall >= computerPlayer.getBalance()) {
                computerPlayer.placeBet(computerPlayer.getBalance());
                pot += computerPlayer.getBalance();
            } else {
                computerPlayer.placeBet(amountToCall);
                pot += amountToCall;
            }
        } else {
            // Do nothing, move to the next player
        }
        isBetMade = true;
    }
}

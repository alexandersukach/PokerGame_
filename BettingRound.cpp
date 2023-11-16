#include "BettingRound.h"
#include <iostream>
#include <cstdlib>
#include <queue>
#include "Player.h"  // Include the Player class header file

using namespace std;

BettingRound::BettingRound(std::queue<Player>& roundPlayers, double minBet)
    : players(roundPlayers), pot(0), currentRoundBet(0), isBetMade(false), isRaiseMade(false), isReRaiseMade(false), minRoundBet(minBet) {}

void BettingRound::playRound() {
    int playersChecked = 0;

    while (!players.empty()) {
        Player& player = players.front();

        isBetMade = false;
        isRaiseMade = false;

        if (!player.isComputer()) {
            handleNoBetMadePlayerActions(player);

            // Check if the player has checked
            if (player.getCurrentBet() == currentRoundBet) {
                playersChecked++;
            }
        } else {
            handleCPUActions(player);

            // Check if the CPU player has checked
            if (player.getCurrentBet() == currentRoundBet) {
                playersChecked++;
            }
        }
        players.push(player);
        players.pop();
    }
    if (playersChecked == players.size()) {
        cout << "All players have checked. Ending the round." << endl;
    }
}

void BettingRound::handleNoBetMadePlayerActions(Player& user) {
    bool validBet = false;

    while (!validBet) {
        cout << "Your current bet: " << user.getCurrentBet() << endl;
        cout << "Action to you. Would you like to (b)et or (c)heck?" << endl;
        char action;
        cin >> action;
        action = tolower(action);

        switch (action) {
            case 'b':
                validBet = makeBet(user);
                if (validBet) {
                    cout << "You have bet." << endl;
                    isBetMade = true;
                }
                break;
            case 'c':
                cout << "\nYou check. Action passed to the next player" << endl;
                validBet = true;
                break;
            default:
                cout << "\nInvalid choice. Try again." << endl;
        }

        // Move to the next player in the queue (either human or computer)
        Player nextPlayer = players.front();
        players.pop();
        players.push(nextPlayer);
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

    switch (action) {
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
            cout << "\nHow much would you like to raise by?";
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
                cout << "\nRaise must be at least twice the initial bet and within your budget." << endl;
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

    switch (action) {
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

bool BettingRound::allPlayersFinishedBetting() const {
    queue<Player> tempQueue = players; // Create a copy of the queue

    while (!tempQueue.empty()) {
        const Player& player = tempQueue.front();
        if (!player.hasFolded() && player.getCurrentBet() < currentRoundBet) {
            return false;
        }
        tempQueue.pop();
    }

    return true;
}

// Other member functions for getting pot, currentRoundBet, etc.



























































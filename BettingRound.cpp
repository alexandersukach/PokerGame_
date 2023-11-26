#include "BettingRound.h"
#include "Player.h" // Include the Player class header file
#include <cstdlib>
#include <iostream>
#include <queue>

using namespace std;

BettingRound::BettingRound(const std::queue<Player> &roundPlayers,
                           double minBet)
    : players(roundPlayers), activePlayers(roundPlayers), pot(0),
      currentRoundBet(0), isBetMade(false), isRaiseMade(false),
      isReRaiseMade(false), minRoundBet(minBet) {}

double BettingRound::getPot() { return pot; }

void BettingRound::playRound() {
  bool roundCompleted = false;

  while (!roundCompleted) {
    Player &player = players.front();
    isBetMade = false;
    isRaiseMade = false;
    isReRaiseMade = false;

    handleNoBetMadePlayerActions(player);
    /*
        Player &player = players.front();
        isBetMade = false;
        isRaiseMade = false;

        if (!player.isComputer()) {
          handleNoBetMadePlayerActions(player);
          if (allPlayersChecked()) {
            cout << "All players have checked. Ending the round." << endl;
            roundCompleted = true;
            cout << currentRoundBet;
          }
        } else {
          handleCPUActions(player);
          player.check(true);
          if (allPlayersChecked()) {
            cout << "All players have checked. Ending the round." << endl;
            roundCompleted = true;
            cout << currentRoundBet;
          }
        }

        Player nextPlayer(players.front());

        players.pop()*/
  }
}

bool BettingRound::allPlayersChecked() const {
  std::queue<Player> tempQueue = players;

  while (!tempQueue.empty()) {
    Player player = tempQueue.front();
    tempQueue.pop();

    if (!player.hasFolded() && !player.hasChecked()) {
      return false;
    }
  }

  return true;
}
void BettingRound::handleNoBetMadePlayerActions(Player &user) {
  bool validBet = false;
  while (!validBet) {
    cout << "Action to you. Would you like to (b)et or (c)heck?" << endl;
    char action;
    cin >> action;
    action = tolower(action);

    switch (action) {
    case 'b':
      cout << "How much would you like to bet? ";
      double betAmount;
      cin >> betAmount;
      if (betAmount >= 2 * minRoundBet && betAmount <= user.getBalance()) {
        user.placeBet(betAmount);
        validBet = true;
        isBetMade = true;
        currentRoundBet = currentRoundBet += betAmount;
        pot += betAmount;
      } else {
        cout
            << "\nBet must be at least twice the minimum and within your budget"
            << endl;
      }

      // validBet = makeBet(user);
      if (validBet) {
        cout << endl << "You have bet." << endl;
        cout << "Your current bet: " << user.getCurrentBet() << endl << endl;
        isBetMade = true;
        cout << "Current round bet: " << currentRoundBet << endl;
        break;
      }

    case 'c':
      user.check(true);
      cout << "\nYou check. Action passed to the next player" << endl;
      // validBet = true;
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

void BettingRound::handleBetMadePlayerActions(Player &user) {
  cout
      << "Someone placed a bet. Would you like to (c)all, (f)old, or (r)aise? ";
  char action;
  cin >> action;
  action = tolower(action);
  double amountToCall = currentRoundBet - user.getCurrentBet();

  switch (action) {
  case 'c':
    if (amountToCall >= user.getBalance()) {
      cout << "You're forced to go all-in!" << endl;
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
    playerRaisesAction(user);
    isRaiseMade = true;
    break;
  default:
    cout << "\nInvalid action...try again" << endl;
  }
}

void BettingRound::playerRaisesAction(Player &user) {
  cout << "\nHow much would you like to raise by? ";
  double raiseAmount;
  cin >> raiseAmount;
  if (raiseAmount == user.getBalance()) {
    cout << "You're forced to go all-in!" << endl;
    user.placeBet(user.getBalance());
  } else if (raiseAmount >= 2 * currentRoundBet &&
             raiseAmount < user.getBalance()) {
    cout << "You raised by " << raiseAmount << "; next player..." << endl;
    user.placeBet(raiseAmount);
    isRaiseMade = true;
    currentRoundBet += raiseAmount;
    pot += raiseAmount;
  } else {
    cout << "Not a valid raise....Must be at least twice the current round bet "
            "and within your budget."
         << endl;
    playerRaisesAction(user); // Ask for raise amount again
  }
}

/*
oid BettingRound::handleBetMadePlayerActions(Player &user) {
  cout
      << "CPU has placed a bet. Would you like to (c)all, (f)old, or (r)aise? ";
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
      cout << "\nRaise must be at least twice the initial bet and within your "
              "budget."
           << endl;
    }
    break;
  default:
    cout << "\nInvalid action. Try again." << endl;
  }
}*/

void BettingRound::handleRaiseMadePlayerActions(Player &user) {
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

void BettingRound::handleNoBetCPUActions(Player &computerPlayer) {
  double randomValue = static_cast<double>(rand()) / RAND_MAX;
}
void BettingRound::handleCPUActions(Player &computerPlayer) {
  double randomValue = static_cast<double>(rand()) / RAND_MAX;

  if (isRaiseMade) {
    // Adjust probabilities based on the current game state
    double callProbability = 0.6;

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
    // Adjust probabilities based on the current game state
    double callProbability = 0.5;
    double raiseProbability = 0.2;

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
    // Adjust probabilities based on the current game state
    double callProbability = 0.6;

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

// Other member functions for getting pot, currentRoundBet, etc.

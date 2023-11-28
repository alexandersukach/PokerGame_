#include "BettingRound.h"
#include "Player.h" // Include the Player class header file
#include <cstdlib>
#include <iostream>
#include <queue>

using namespace std;

BettingRound::BettingRound(std::queue<Player> playerQueue, int minBet)
    : players(std::move(playerQueue)), minRoundBet(minBet), currentRoundBet(0),
      pot(0), isBetMade(true), isRaiseMade(true) {}

void BettingRound::playRound() {
  bool roundCompleted = false;

  while (!roundCompleted) {
    Player &player = players.front();
    isBetMade = false;
    isRaiseMade = false;

    if (!player.isComputer()) {
      handlePlayerActions(player);
      if (allPlayersChecked()) {
        cout << "All players have checked. Ending the round." << endl;
        roundCompleted = true;
      }
    } else {
      handleCPUActions(player);
      if (allPlayersChecked()) {
        cout << "All players have checked. Ending the round." << endl;
        roundCompleted = true;
      }
    }

    // Print each player's action
    cout << player.getName() << " ";
    if (player.hasFolded()) {
      cout << "folds." << endl;
    } else if (player.hasChecked()) {
      cout << "checks." << endl;
    } else {
      cout << "bets " << player.getCurrentBet() << "." << endl;
    }

    players.pop();
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
int BettingRound::getPot() { return pot; }

void BettingRound::handleNoBetMadePlayerActions(Player &user) {
  char action;

  do {
    cout << "Action to you...would you like to (b)et or (c)heck?";
    cin >> action;
    action = tolower(action);

    switch (action) {
    case 'b':
      int amountToBet;
      do {
        cout << "How much would you like to bet? ";
        cin >> amountToBet;
        if (amountToBet == user.getBalance()) {
          cout << "You are going all in!!!" << endl;
        }
        if (amountToBet >= 20 && amountToBet <= user.getBalance()) {
          user.placeBet(amountToBet);
          isBetMade = true;
          pot += amountToBet;
          currentRoundBet += amountToBet;
        } else {
          cout << "Invalid bet amount. Please try again." << endl;
        }
      } while (!isBetMade);
      break;
    case 'c':
      cout << "You check. Action passed to the next player." << endl;
      user.check();
      break;
    default:
      cout << "Invalid option, please select a valid option." << endl;
    }
  } while (action != 'c'); // action != 'b' &&
}
void BettingRound::handleBetMadePlayerActions(Player &user) {
  char action;
  int amountToCall = currentRoundBet - user.getCurrentBet();
  do {
    cout << "Someone has bet. Would you like to (c)all, (r)aise, or (f)old? ";
    cin >> action;
    action = tolower(action);

    switch (action) {
    case 'c':

      cout << user.getName() << " calls by " << amountToCall << "." << endl;
      user.call(amountToCall);
      break;
    case 'r':
      handleRaiseMadePlayerActions(user);
      break;
    case 'f':
      cout << user.getName() << " folds." << endl;
      user.fold();
      break;
    default:
      cout << "Invalid option, please select a valid option." << endl;
    }
  } while (action != 'c' && action != 'r' && action != 'f');
}
void BettingRound::handleRaiseMadePlayerActions(Player &user) {
  int raiseAmount;

  do {
    cout << "How much would you like to raise? ";
    cin >> raiseAmount;

    if (raiseAmount >= 2 * currentRoundBet &&
        raiseAmount <= user.getBalance()) {
      if (raiseAmount == user.getBalance()) {
        cout << user.getName() << " is going all-in!" << endl;
      }

      user.raise(raiseAmount);
      isRaiseMade = true;
      currentRoundBet += raiseAmount;
      pot += raiseAmount;

      cout << endl << user.getName() << " has raised." << endl;
      cout << user.getName() << "'s current bet: " << user.getCurrentBet()
           << endl
           << endl;
    } else {
      cout << "\nInvalid raise amount. Please try again." << endl;
    }
  } while (raiseAmount < 2 * currentRoundBet ||
           raiseAmount > user.getBalance());
}

int getRandomBetAmount(const Player &computerPlayer) {
  int minBet = 20;
  int maxBet = computerPlayer.getBalance();
  return rand() % (maxBet - minBet + 1) + minBet;
}

void BettingRound::handleNoBetMadeCPUActions(Player &computerPlayer) {
  int randomValue = rand() % 100;

  if (randomValue < 50) {
    int betAmount = getRandomBetAmount(computerPlayer);
    cout << computerPlayer.getName() << " bets " << betAmount << "." << endl;
    computerPlayer.placeBet(betAmount);
    isBetMade = true; // Update isBetMade for the computer player
    pot += betAmount;
    currentRoundBet += betAmount;
  } else {
    cout << computerPlayer.getName() << " checks." << endl;
    // Do nothing, move to the next player
  }

  // Update isBetMade for the user player
  if (!isBetMade) {
    isBetMade = true;
  }
}

void BettingRound::handleBetMadeCPUActions(Player &computerPlayer) {
  int randomValue = rand() % 100;

  if (randomValue < 60) {
    int amountToCall = currentRoundBet - computerPlayer.getCurrentBet();
    if (amountToCall >= computerPlayer.getBalance()) {
      computerPlayer.call(computerPlayer.getBalance());
      pot += computerPlayer.getBalance();
    } else {
      computerPlayer.call(amountToCall);
      pot += amountToCall;
    }
  } else if (randomValue < 80) {
    int raiseAmount = 2 * currentRoundBet;
    if (raiseAmount >= computerPlayer.getBalance()) {
      computerPlayer.raise(computerPlayer.getBalance());
      pot += computerPlayer.getBalance();
    } else {
      computerPlayer.raise(raiseAmount);
      pot += raiseAmount;
    }
    isRaiseMade = true;
  } else {
    cout << "Computer folds." << endl;
    computerPlayer.fold();
  }
}

void BettingRound::handleRaiseMadeCPUActions(Player &computerPlayer) {
  int randomValue = rand() % 100;

  if (randomValue < 70) {
    int amountToCall = currentRoundBet - computerPlayer.getCurrentBet();
    if (amountToCall >= computerPlayer.getBalance()) {
      computerPlayer.call(computerPlayer.getBalance());
      pot += computerPlayer.getBalance();
    } else {
      computerPlayer.call(amountToCall);
      pot += amountToCall;
    }
  } else {
    cout << "Computer folds." << endl;
    computerPlayer.fold();
  }
}

void BettingRound::handlePlayerActions(Player &user) {
  if (!isBetMade) {
    handleNoBetMadePlayerActions(user);
  } else {
    handleBetMadePlayerActions(user);
  }
}

void BettingRound::handleCPUActions(Player &computerPlayer) {
  if (!isBetMade) {
    handleNoBetMadeCPUActions(computerPlayer);
  } else {
    handleBetMadeCPUActions(computerPlayer);
  }
}

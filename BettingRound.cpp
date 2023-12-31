#include "BettingRound.h"
#include "Player.h"
#include <cstdlib>
#include <iostream>
#include <queue>

using namespace std;

BettingRound::BettingRound(queue<Player> playerQueue)
    : players(move(playerQueue)), currentRoundBet(0), pot(0), isBetMade(true),
      isRaiseMade(true) {}

int BettingRound::getPot() { return pot; }

bool BettingRound::allPlayersChecked() const {
  queue<Player> tempQueue = players;

  while (!tempQueue.empty()) {
    Player player = tempQueue.front();
    tempQueue.pop();

    if (!player.hasFolded() && !player.hasChecked()) {
      return false;
    }
  }
  return true;
}

bool BettingRound::allPlayersCalled() const {
  queue<Player> tempQueue = players;

  while (!tempQueue.empty()) {
    Player player = tempQueue.front();
    tempQueue.pop();

    if (!player.hasFolded() && !player.hasCalled()) {
      return false;
    }
  }
  return true;
}

void BettingRound::playRound() {
  bool roundCompleted = false;

  while (!roundCompleted) {
    Player &player = players.front();
    isBetMade = false;
    isRaiseMade = false;

    if (allPlayersChecked()) {
      cout << "All players have checked. Ending betting round." << endl;
      roundCompleted = true;
    }

    if (allPlayersCalled()) {
      cout << "All players have either called or folded. Ending betting round."
           << endl;
      roundCompleted = true;
    }

    if (!player.isComputer()) {
      if (isRaiseMade) {
        handleRaiseMadePlayerActions(player);
      } else if (isBetMade) {
        handleBetMadePlayerActions(player);
      } else {
        handleNoBetMadePlayerActions(player);
      }
    } else {
      if (isRaiseMade) {
        handleRaiseMadeCPUActions(player);
      } else if (isBetMade) {
        handleBetMadeCPUActions(player);
      } else {
        handleNoBetMadeCPUActions(player);
      }
    }

    players.pop();
    players.push(player);
  }
}

void BettingRound::handleNoBetMadePlayerActions(Player &user) {
  char action;

  cout << "Action to you...would you like to (b)et or (c)heck?";
  cin >> action;
  action = tolower(action);

  switch (action) {
  case 'b':
    int amountToBet;
    cout << "How much would you like to bet? ";
    cin >> amountToBet;

    if (amountToBet == user.getBalance()) {
      cout << "You are going all in!!!" << endl;
    }

    if (amountToBet > 0 && amountToBet <= user.getBalance()) {
      user.placeBet(amountToBet);
      isBetMade = true;
      pot += amountToBet;
      currentRoundBet += amountToBet;
    } else {
      cout << "Bet must be a positive number and within your budget." << endl;
    }
    break;
  case 'c':
    cout << "You check. Action passed to the next player." << endl;
    user.check();
    break;
  default:
    cout << "Invalid option, please select a valid option." << endl;
  }
}

void BettingRound::handleBetMadePlayerActions(Player &user) {
  char action;
  int amountToCall = currentRoundBet - user.getCurrentBet();

  cout << "Someone has bet. Would you like to (c)all, (r)aise, or (f)old? ";
  cin >> action;
  action = tolower(action);

  switch (action) {
  case 'c':
    cout << user.getName() << " calls by " << amountToCall << "." << endl;
    user.call(amountToCall);
    break;
  case 'r':
    int amountToRaise;
    cout << "How much would you like to raise by? ";
    cin >> amountToRaise;

    if (amountToRaise == user.getBalance()) {
      cout << "You are going all in!!!" << endl;
    }

    if (amountToRaise > 0 && amountToRaise <= user.getBalance()) {
      user.placeBet(amountToRaise);
      isBetMade = true;
      pot += amountToRaise;
      currentRoundBet += amountToRaise;
    } else {
      cout << "Bet must be a positive number and within your budget." << endl;
    }
    break;
  case 'f':
    cout << user.getName() << " folds." << endl;
    user.fold();
    break;
  default:
    cout << "Invalid option, please select a valid option." << endl;
  }
}

void BettingRound::handleRaiseMadePlayerActions(Player &user) {
  char action;
  int amountToCall = currentRoundBet - user.getCurrentBet();

  cout << "Someone has raised. Would you like to (c)all " << amountToCall
       << ", or (f)old?";
  cin >> action;

  switch (action) {
  case 'c':
    cout << user.getName() << " calls by " << amountToCall << "." << endl;
    user.call(amountToCall);
    break;
  case 'f':
    cout << user.getName() << " folds." << endl;
    break;
  default:
    cout << "Invalid option, please select a valid option." << endl;
  }
}

int getRandomBetAmount(const Player &computerPlayer) {
  int minBet = 1;
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
  // if (!isBetMade) {
  //   isBetMade = true;
  // }
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
  if (isRaiseMade) {
    handleRaiseMadePlayerActions(user);
  } else if (!isBetMade) {
    handleNoBetMadePlayerActions(user);
  } else {
    handleBetMadePlayerActions(user);
  }
}

void BettingRound::handleCPUActions(Player &computerPlayer) {
  if (currentRoundBet > 0) {
    handleBetMadeCPUActions(computerPlayer);
  } else {
    handleNoBetMadeCPUActions(computerPlayer);
  }
}

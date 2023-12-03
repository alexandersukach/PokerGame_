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
  isBetMade = false;
  isRaiseMade = false;

  for (;;) {
    if (allPlayersChecked()) {
      cout << "All players have checked. Ending betting round." << endl;
      break;
    }

    if (allPlayersCalled()) {
      cout << "All players have either called or folded. Ending betting round."
           << endl;
      break;
    }

    Player &player = players.front();

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
  cout << "Your current balance: $" << user.getBalance() << endl;
  cout << "Your current bet: $" << user.getCurrentBet() << endl;
  cout << "The current round bet: $" << currentRoundBet << endl;
  cout << "Action to you...would you like to (b)et or (c)heck?";
  cin >> action;
  action = tolower(action);

  switch (action) {
  case 'b':
    if (!user.isAllIn() && !user.hasFolded()) { // && or ||
      int amountToBet;
      cout << "How much would you like to bet? $";
      cin >> amountToBet;

      if (amountToBet == user.getBalance()) {
        cout << "You are going all in!!!" << endl;
        user.shove();
      }

      if (amountToBet > 0 && amountToBet <= user.getBalance()) {
        user.placeBet(amountToBet);
        isBetMade = true;
        pot += amountToBet;
        currentRoundBet += amountToBet;
        user.setCurrentBet(amountToBet);
      } else {
        cout << "Invalid bet! Please enter a value greater than 0 and within "
                "your budget of $"
             << user.getBalance() << endl;
      }
    } else if (user.hasFolded()) {
      cout << "You cannot bet; You have folded." << endl;
    } else {
      cout << "You cannot bet more...you are already all in." << endl;
    }
    break;
  case 'c':
    cout << "You check. Action passed to the next player." << endl;
    break;
  default:
    cout << "Invalid input, try again." << endl;
  }
}

void BettingRound::handleBetMadePlayerActions(Player &user) {
  char action;
  int amountToCall = currentRoundBet - user.getCurrentBet();
  cout << "Your current balance: $" << user.getBalance() << endl;
  cout << "Your current bet: $" << user.getCurrentBet() << endl;
  cout << "The current round bet: $" << currentRoundBet << endl;

  cout << "Someone has bet. Would you like to (c)all $" << amountToCall
       << ", (r)aise, or (f)old?";
  cin >> action;

  switch (action) {
  case 'c':
    if (!user.isAllIn() && !user.hasFolded()) { // && or ||
      if (amountToCall >= user.getBalance()) {
        cout << "You are going all in!" << endl;
        user.shove();
      }
      user.call(amountToCall);
      user.setCurrentBet(amountToCall);
    } else if (user.hasFolded()) {
      cout << "You cannot do anything, you have folded." << endl;
    } else {
      cout << "You cannot do anything...you are already all-in." << endl;
    }
    break;
  case 'r':
    if (!user.isAllIn() && !user.hasFolded()) {
      int amountToRaise;
      cout << "How much would you like to raise by? ";
      cin >> amountToRaise;

      if (amountToRaise > 0 && amountToRaise <= user.getBalance()) {
        user.raise(amountToRaise);
        isRaiseMade = true;
        pot += amountToRaise;
        user.setCurrentBet(amountToRaise);
        currentRoundBet += amountToRaise;
      } else {
        cout << "Invalid raise...must be at least $1 and within your budget of "
             << user.getBalance() << "." << endl;
      }
    } else if (user.hasFolded()) {
      cout << "You cannot raise...you have folded." << endl;
    } else {
      cout << "You cannot raise...you are already all-in." << endl;
    }
    break;
  default:
    cout << "Invalid input, try again." << endl;
  }
}

void BettingRound::handleRaiseMadePlayerActions(Player &user) {
  char action;
  int amountToCall = currentRoundBet - user.getCurrentBet();
  cout << "Your current balance: $" << user.getBalance() << endl;
  cout << "Your current bet: $" << user.getCurrentBet() << endl;
  cout << "The current round bet: $" << currentRoundBet << endl;

  cout << "Someone has raised. Would you like to (c)all $" << amountToCall
       << " or (f)old? ";
  cin >> action;

  switch (action) {
  case 'c':
    if (!user.isAllIn() && !user.hasFolded()) {
      if (amountToCall >= user.getBalance()) {
        user.shove();
        user.call();
      }
      user.call(amountToCall);
      user.setCurrentBet(amountToCall);
    } else if (user.hasFolded()) {
      cout << "You cannot do anything, you have folded." << endl;
    } else {
      cout << "You cannot do anything...you are already all-in." << endl;
    }
    break;
  case 'f':
    cout << "You have folded." << endl;
    user.fold();
    break;
  default:
    cout << "Invalid input, try again." << endl;
  }
}

int getRandomBetAmount(const Player &computerPlayer) {
  int minBet = 1;
  int maxBet = computerPlayer.getBalance();
  return rand() % (maxBet - minBet + 1) + minBet;
}
void BettingRound::handleNoBetMadeCPUActions(Player &computerPlayer) {
  int randomValue = rand() % 100;

  if (randomValue < 30) {
    int betAmount = getRandomBetAmount(computerPlayer);
    betAmount = min(
        betAmount,
        computerPlayer.getBalance()); // Ensure it doesn't exceed the balance
    cout << computerPlayer.getName() << " bets " << betAmount << "." << endl;
    computerPlayer.placeBet(betAmount);
    isBetMade = true;
    pot += betAmount;
    currentRoundBet += betAmount;
    computerPlayer.setCurrentBet(betAmount);
  } else {
    cout << computerPlayer.getName() << " checks." << endl;
    computerPlayer.check();
    // Do nothing, move to the next player
  }
}

void BettingRound::handleBetMadeCPUActions(Player &computerPlayer) {
  int randomValue = rand() % 100;

  if (randomValue < 40) {
    int amountToCall = currentRoundBet - computerPlayer.getCurrentBet();
    if (amountToCall >= computerPlayer.getBalance()) {
      computerPlayer.call(computerPlayer.getBalance());
      pot += computerPlayer.getBalance();
      computerPlayer.setCurrentBet(computerPlayer.getBalance());
    } else {
      int raiseAmount = getRandomBetAmount(computerPlayer);
      raiseAmount =
          min(raiseAmount,
              computerPlayer.getBalance() -
                  amountToCall); // Ensure it doesn't exceed the balance
      computerPlayer.raise(raiseAmount);
      pot += raiseAmount;
      cout << computerPlayer.getName() << " raises by $" << raiseAmount
           << "...next player..." << endl;
      currentRoundBet += raiseAmount;
      computerPlayer.setCurrentBet(currentRoundBet);
      pot += raiseAmount;
      isRaiseMade = true;
    }
  } else if (randomValue < 60) {
    // Existing code for calling
  } else {
    cout << computerPlayer.getName() << " folds." << endl;
    computerPlayer.fold();
  }
}

void BettingRound::handleRaiseMadeCPUActions(Player &computerPlayer) {
  int randomValue = rand() % 100;

  if (randomValue < 50) {
    int amountToCall = currentRoundBet - computerPlayer.getCurrentBet();
    if (amountToCall >= computerPlayer.getBalance()) {
      computerPlayer.call(computerPlayer.getBalance());
      pot += computerPlayer.getBalance();
      computerPlayer.setCurrentBet(computerPlayer.getBalance());
    } else {
      computerPlayer.call(amountToCall);
      pot += amountToCall;
      computerPlayer.setCurrentBet(currentRoundBet);
    }
  } else {
    cout << computerPlayer.getName() << " folds." << endl;
    computerPlayer.fold();
  }
}
void BettingRound::handlePlayerActions(Player &user) {
  if (user.isAllIn()) {
    cout << user.getName()
         << " is all-in and will sit out of the following betting rounds."
         << endl;
    return;
  }

  if (isRaiseMade) {
    handleRaiseMadePlayerActions(user);
  } else if (!isBetMade) {
    handleNoBetMadePlayerActions(user);
  } else {
    handleBetMadePlayerActions(user);
  }
}

void BettingRound::handleCPUActions(Player &computerPlayer) {
  if (computerPlayer.isAllIn()) {
    cout << computerPlayer.getName()
         << " is all-in and will sit out of the following betting rounds."
         << endl;
    return;
  }

  if (currentRoundBet > 0) {
    handleBetMadeCPUActions(computerPlayer);
  } else {
    handleNoBetMadeCPUActions(computerPlayer);
  }
}

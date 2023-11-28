Poker Game - C++



BETTING ROUND....

// void BettingRound::handleNoBetMadePlayerActions(Player &user) {
//   char action;

//   do {
//     cout << "No action so far...would you like to (b)et or (c)heck? " <<
//     endl; cin >> action; action = tolower(action);

//     switch (action) {
//     case 'b':
//       double betAmount;
//       cout << "How much would you like to bet? ";
//       cin >> betAmount;

//       if (betAmount >= 2 * minRoundBet && betAmount <= user.getBalance()) {
//         if (betAmount == user.getBalance()) {
//           cout << "\nYou're going all-in!" << endl;
//         }
//         user.placeBet(betAmount);
//         isBetMade = true;
//         currentRoundBet += betAmount;
//         pot += betAmount;
//         cout << endl << "You have bet." << endl;
//         cout << "Your current bet: " << user.getCurrentBet() << endl << endl;
//       } else {
//         cout << "\nInvalid bet amount. Please try again." << endl;
//       }
//       break;
//     case 'c':
//       user.check(true);
//       cout << "\nYou check...action passed to the next player." << endl;
//       break;
//     default:
//       cout << "\nInvalid choice. Try again." << endl;
//     }
//   } while (action != 'b' || action != 'c');
// }

// void BettingRound::handleBetMadePlayerActions(Player &user) {
//   cout
//       << "Someone placed a bet. Would you like to (c)all, (f)old, or (r)aise?
//       ";
//   char action;
//   cin >> action;
//   action = tolower(action);
//   int amountToCall = currentRoundBet - user.getCurrentBet();

//   switch (action) {
//   case 'c':
//     if (amountToCall >= user.getBalance()) {
//       cout << "You're forced to go all-in!" << endl;
//       user.placeBet(user.getBalance());
//       pot += user.getBalance();
//     } else {
//       cout << "You call, next player..." << endl;
//       user.placeBet(amountToCall);
//       pot += amountToCall;
//     }
//     user.hasCalled(true);

//     break;
//   case 'f':
//     cout << "You folded your hand." << endl;
//     user.fold(true);
//     break;
//   case 'r':
//     handlePlayerRaisesAction(user);
//     isRaiseMade = true;
//     break;
//   default:
//     cout << "\nInvalid action...try again" << endl;
//   }
// }

// void BettingRound::handlePlayerRaisesAction(Player &user) {
//   cout << "\nHow much would you like to raise by? ";
//   int raiseAmount;
//   cin >> raiseAmount;
//   if (raiseAmount == user.getBalance()) {
//     cout << "You're forced to go all-in!" << endl;
//     user.placeBet(user.getBalance());
//   } else if (raiseAmount >= 2 * currentRoundBet &&
//              raiseAmount < user.getBalance()) {
//     cout << "You raised by " << raiseAmount << "; next player..." << endl;
//     user.placeBet(raiseAmount);
//     isRaiseMade = true;
//     currentRoundBet += raiseAmount;
//     pot += raiseAmount;
//   } else {
//     cout << "Not a valid raise....Must be at least twice the current round
//     bet "
//             "and within your budget."
//          << endl;
//     handlePlayerRaisesAction(user); // Ask for raise amount again
//   }
// }

/*
oid BettingRound::handleBetMadePlayerActions(Player &user) {
  cout
      << "CPU has placed a bet. Would you like to (c)all, (f)old, or (r)aise? ";
  char action;
  cin >> action;
  action = tolower(action);
  int amountToCall = (currentRoundBet - user.getCurrentBet());

  switch (action) {
  case 'c':
    if (amountToCall >= user.getBalance()) {
      cout << "You're forced to go all in!" << endl;
      user.placeBet(user.getBalance());
      pot
       += user.getBalance();
    } else {
      cout << "You call, next player..." << endl;
      user.placeBet(amountToCall);
      pot
       += amountToCall;
    }
    break;
  case 'f':
    cout << "You folded your hand." << endl;
    user.fold();
    break;
  case 'r':
    cout << "\nHow much would you like to raise by?";
    int raiseAmount;
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
      pot
       += raiseAmount;
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
  int amountToCall = currentRoundBet - user.getCurrentBet();

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
  int randomValue = static_cast<int>(rand()) / RAND_MAX;
}
void BettingRound::handleCPUActions(Player &computerPlayer) {
  int randomValue = static_cast<int>(rand()) / RAND_MAX;

  if (isRaiseMade) {
    // Adjust probabilities based on the current game state
    int callProbability = 0.6;

    if (randomValue <= callProbability) {
      int amountToCall = currentRoundBet - computerPlayer.getCurrentBet();
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
    int callProbability = 0.5;
    int raiseProbability = 0.2;

    if (randomValue <= callProbability) {
      int amountToCall = currentRoundBet - computerPlayer.getCurrentBet();
      if (amountToCall >= computerPlayer.getBalance()) {
        computerPlayer.placeBet(computerPlayer.getBalance());
        pot += computerPlayer.getBalance();
      } else {
        computerPlayer.placeBet(amountToCall);
        pot += amountToCall;
      }
    } else if (randomValue <= (callProbability + raiseProbability)) {
      int raiseAmount = 2 * currentRoundBet;
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
    int callProbability = 0.6;

    if (randomValue <= callProbability) {
      int amountToCall = currentRoundBet - computerPlayer.getCurrentBet();
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

// Other member functions for getting pot

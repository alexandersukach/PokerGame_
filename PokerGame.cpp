#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>
#include <vector>
#include <stack>
#include <string>
#include <cctype> 
#include <queue>
#include <algorithm>
#include <random>

using namespace std;



class Round {
    private:

    int bettingRound;
    queue<Player> players;
    int pot;
    int currentRoundBet;
    bool isBetMade;

    public:

    Round(int number, queue<Player>& roundPlayers) {
        bettingRound = number;
        players = roundPlayers;
        pot = 0;
        currentRoundBet = 0;
        isBetMade = false;
    }

        bool firstPlayerBet() {
        // EMPTY AT THE MOMENT 
    }
    void playRound() {

        if(isBetMade) {
            void handleBetMadeActions();
        } else {
            handleNoBetActions();
        }
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

        //? bool isRaiseMade = false;          // somehow cover that a raise is made 
        if (isRaiseMade) {
            betProbability = 0.0; // Only options are to call or fold
            callProbability = 0.6;
            foldProbability = 0.4;
        }

        


    }
}
class Game {
    private:
    vector<Card> communityCards[]; // Max 5
    vector<Card> playerHoleCards[5][2]; // Two cards per player, maximum 5 players
    /*
    I could just set it 5 (max number players) and deal the cards while the first argument hasn't reached 5*/
    vector<Card> combinedHand[5][7]; // Should i Just make them all empty
    queue<Player> players;
    Deck gameDeck;

    public:

    Game() : gameDeck() {
        // Initialize other game-related data here
    }

    void initializePlayers(int numOpponents, const string& playerName, int startingBalance) {
        players.push(Player(playerName, startingBalance));

        for(int i = 0; i < numOpponents; i++) {
            string opponentName;
            cout << "Enter opponent " << i + 1 << "'s name: ";
            cin >> opponentName;
            players.push(Player(opponentName, startingBalance));
        }
    }
    // Dealing player cards

    void dealHoleCards() {
        for(int i = 0; i < 2; i++) {
            for(Player& player: players) {
                for(int cardIndex = 0; cardIndex < 2; cardIndex++) {
                    for(int playerIndex = 0; playerIndex < 5; playerIndex++) {
                        playerHoleCards[playerIndex][cardIndex] = gameDeck.dealCard();
                    }
                }
            }
        }
    }

    // Dealing community cards 

    void dealFlop() {
        gameDeck.burnCard();
        for(int i = 0; i < 3; i++) {
            communityCards[i] = gameDeck.dealCard();
        }
    }

    void dealTurn() {
        gameDeck.burnCard();
        communityCards[3] = gameDeck.dealCard();
    }

    void dealRiver() {
        gameDeck.burnCard();
        communityCards[4] = gameDeck.dealCard();
    }

    // Combining community cards and each player's cards to compare hand strength

void combineHands() {
    for (int playerIndex = 0; playerIndex < players.size(); playerIndex++) {
        // Clear previous combined hand
        for (int i = 0; i < 7; i++) {
            combinedHands[playerIndex][i].clear();
        }

        // Combine the player's hole cards
        for (int i = 0; i < 2; i++) {
            for (const Card& playerCard : playerHoleCards[playerIndex][i]) {
                combinedHands[playerIndex][i].push_back(playerCard);
            }
        }

        // Combine with community cards
        for (int i = 2; i < 7; i++) {
            for (const Card& communityCard : communityCards[i - 2]) {
                combinedHands[playerIndex][i].push_back(communityCard);
             }
            }
        }
    }
    // Moving min elemetn to front?

void selectionSortCombinedHands(int playerIndex) {
        for (int i = 0; i < 6; i++) {
            int minIndex = i;
            for(int j = 1; j < 7; j++) {
                int rank1 = combinedHand[playerIndex][minIndex].getRank();
                int rank2 = combinedHand[playerIndex][j].getRank();

                if (rank1 > rank2) {
                    minIndex = j;
                }
            }
            if (minIndex != i) {
                swap(combinedHand[playerIndex][i], combinedHand[playerIndex][minIndex]);
            }
            
        }
    }



};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main() {
    Game game;
    int pot = 0;

    //If big blind remove 10 if small blind remove 5 add to pot...



    int numOpponents;
    cout << "Enter number of players, other than yourself: ";
    cin >> numOpponents;

    string userName;
    cout << "Enter your name: ";
    cin >> userName;

    int userStartingBalance; // The same for all players
    cout << "Enter your starting balance: ";
    cin >> userStartingBalance;

    game.initializePlayers(numOpponents, userName, userStartingBalance);
    Necessary
    game.dealHoleCards();
    
    game.dealFlop();

    game.dealTurn();

    game.dealRiver();


bool isBigBlind, isSmallBlind;
if (!isBigBlind) {
    if(isSmallBlind) {
        char actionSmallBlind;
        cout << "Would you like to (c)all $5 or (f)old?";
        cin >> actionSmallBlind;
        actionSmallBlind = tolower(actionSmallBlind);
        switch (actionSmallBlind) {
            case 'c': {
                userPlayer.makeBet(5);
                break;
            case 'f': {
                userPlayer.fold();
                break;
            default:
                cout << "Choose valid option";
            }
            }
        }
    }
}

bool betMade;
int betToBeCalled;
if(betMade) {
    char actionBetMade;
    cout << "Would you like to (c)all, (f)old, or (r)aise?";
    cin >> actionBetMade;
    actionBetMade = tolower(actionBetMade);
    switch(actionBetMade) {
        case 'c':
            userPlayer.makeBet(betToBeCalled);
            break;
        case 'f':
            userPlayer.fold();
            break;
        case 'r':
            userPlayer.reraise()
            betTobeCalled = the reraise //need to do some math to subtract so other players know what to put in
            break;
        default:
            cout << "Choose valid option";
    }
}
// no bet made
else {
    char actionNoBetMade;
    cout << "Would you like to (b)et, (c)heck?";
    cin >> actionNoBetMade;;
    actionNoBetMade = tolower(actionNoBetMade);
    switch(actionNoBetMade) {
        case 'b':
        
} }




}
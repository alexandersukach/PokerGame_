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



class Card {
private:
    Rank rank;
    Suit suit;

public:
    enum Rank { TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };
    enum Suit { HEARTS, CLUBS, DIAMONDS, SPADES };

    Card(Rank r, Suit s) : rank(r), suit(s) {}

    Rank getRank() const { return rank; }
    Suit getSuit() const { return suit; }

    void display() const {
        const char* rankStr[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
        const char* suitStr[] = { "H", "C", "D", "S" };
        cout << rankStr[rank] << suitStr[suit] << endl;
    }
};

bool compareCardsByRank(const Card& a, const Card& b) {
    return a.getRank() < b.getRank();
}

class Hand {
private:
    vector<Card> cards;

    vector<Card> sortCards(const vector<Card>& unsorted) const {
        vector<Card> sorted = unsorted;
        sort(sorted.begin(), sorted.end(), compareCardsByRank);
        return sorted;
    }

public:
    // Constructor to initialize the hand with a vector of cards
    Hand(const vector<Card>& handCards) : cards(handCards) {}

    int calculateScore() const {
        vector<Card> sortedCards = sortCards(cards);

        if (isRoyalFlush(sortedCards)) {
            return 9; // Royal Flush
        } else if (isStraightFlush(sortedCards)) {
            return 8; // Straight Flush
        } else if (isFourOfAKind(sortedCards)) {
            return 7; // Four of a Kind
        } else if (isFullHouse(sortedCards)) {
            return 6; // Full House
        } else if (isFlush(sortedCards)) {
            return 5; // Flush
        } else if (isStraight(sortedCards)) {
            return 4; // Straight
        } else if (isThreeOfAKind(sortedCards)) {
            return 3; // Three of a Kind
        } else if (isTwoPair(sortedCards)) {
            return 2; // Two Pair
        } else if (isOnePair(sortedCards)) {
            return 1; // One Pair
        } else {
            return 0; // High Card
        }
    }

    bool isOnePair() const {
        vector<Card> sortedCards = sortCards(cards);

        for (size_t i = 0; i < sortedCards.size() - 1; i++) {
            if (sortedCards[i].getRank() == sortedCards[i + 1].getRank()) {
                return true;
            }
        }
        return false;
    }

    bool isTwoPair() const {
        vector<Card> sortedCards = sortCards(cards);
        int pairCount = 0;

        for (size_t i = 0; i < sortedCards.size() - 1; i++) {
            if (sortedCards[i].getRank() == sortedCards[i + 1].getRank()) {
                pairCount++;
                i++; // Skip to the next card of the pair
            }
        }
        return pairCount == 2; // Two pairs consist of two pairs (four cards) in total
    }

    bool isThreeOfAKind() const {
        std. vector<Card> sortedCards = sortCards(cards);

        for (size_t i = 0; i < sortedCards.size() - 2; i++) {
            if (sortedCards[i].getRank() == sortedCards[i + 1].getRank() &&
                sortedCards[i + 1].getRank() == sortedCards[i + 2].getRank()) {
                return true;
            }
        }
        return false;
    }

    bool isStraight() const {
        std::vector<Card> sortedCards = sortCards(cards);

        for (size_t i = 1; i < sortedCards.size(); i++) {
            if (sortedCards[i].getRank() != sortedCards[i - 1].getRank() + 1) {
                return false;
            }
        }
        return true;
    }

    bool isFlush() const {
        std::vector<Card> sortedCards = sortCards(cards);

        for (size_t i = 1; i < sortedCards.size(); i++) {
            if (sortedCards[i].getSuit() != sortedCards[0].getSuit()) {
                return false;
            }
        }
        return true;
    }

    bool isFourOfAKind() const {
        std::vector<Card> sortedCards = sortCards(cards);

        for (size_t i = 0; i < sortedCards.size() - 3; i++) {
            if (sortedCards[i].getRank() == sortedCards[i + 1].getRank() &&
                sortedCards[i + 1].getRank() == sortedCards[i + 2].getRank() &&
                sortedCards[i + 2].getRank() == sortedCards[i + 3].getRank()) {
                return true;
            }
        }
        return false;
    }

    bool isStraightFlush() const {
        return isStraight() && isFlush();
    }

    bool isRoyalFlush() const {
        std::vector<Card> sortedCards = sortCards(cards);

        if (sortedCards[0].getRank() == Card::TEN &&
            sortedCards[1].getRank() == Card::JACK &&
            sortedCards[2].getRank() == Card::QUEEN &&
            sortedCards[3].getRank() == Card::KING &&
            sortedCards[4].getRank() == Card::ACE) {
            return isFlush();
        }
        return false;
    }

 int calculateBestHandScore() const {
        int bestScore = 0;

        // Iterate through all combinations of 5 cards
        for (size_t i = 0; i < cards.size() - 4; i++) {
            for (size_t j = i + 1; j < cards.size() - 3; j++) {
                for (size_t k = j + 1; k < cards.size() - 2; k++) {
                    for (size_t m = k + 1; m < cards.size() - 1; m++) {
                        for (size_t n = m + 1; n < cards.size(); n++) {
                            // Create a temporary hand with the selected 5 cards
                            std::vector<Card> tempHand = {cards[i], cards[j], cards[k], cards[m], cards[n]};

                            // Calculate the score for this combination
                            int score = calculateScore(tempHand);

                            // Update the best score if this combination is better
                            if (score > bestScore) {
                                bestScore = score;
                            }
                        }
                    }
                }
            }
        }

        return bestScore;
    }

};


struct CardNode {
    Card card;
    CardNode* next;
    CardNode* prev;

    CardNode(const Card& c) : card(c), next(nullptr), prev(nullptr) {}
};

class DoublyLinkedList {
private:
    CardNode* head;
    CardNode* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    void pushBack(const Card& card) {
        CardNode* newNode = new CardNode(card);
        if (!tail) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void clear() {
        while (head) {
            CardNode* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }

    bool isEmpty() { return head == nullptr; }
};

class Player {
private:
    string name;
    int balance, currentBet;
    bool isBigBlind, isSmallBlind, isFolded;


public:
    Player(const string& playerName, int startingBalance) : name(playerName), balance(startingBalance), bet(0) {}

    int getBalance() const { return balance; }

    void winHand(int pot) { balance += pot; }

    void setCurrentBet(int betMade) { currentBet += betMade};

    void placeBet(int betAmount) { balance -= betAmount; }

    void raise(int raiseAmount) { balance -= raiseAmount; }

    void fold() { isFolded = true; }

    void bigBlindPayment() { balance -= 10; }

    void smallBlindPayment() { balance -= 5; }

    void bigBlind() { isBigBlind = true; }

    void smallBlind() { isSmallBlind = true; }

    void fold() { isFolded = true; } 

    void cpuAction(bool isRaiseMade) {
        double betProbability;
        double callProbability;
        double raiseProbability;
        double foldProbability;
    }
};

class Deck {
    private:
    stack<Card> deck;

    //Not converting enums to ints, but rather using them as loop indices
    void InitializeDeck() {
    for (int suit = Card::HEARTS; suit <= Card::SPADES; suit++) {
        for (int rank = Card::TWO; rank <= Card::ACE; rank++) {
            Rank actualRank;
            if (rank == Card::JACK) {
                actualRank = Card::Rank(11);
            } else if (rank == Card::QUEEN) {
                actualRank = Card::Rank(12);
            } else if (rank == Card::KING) {
                actualRank = Card::Rank(13);
            } else if (rank == Card::ACE) {
                actualRank = Card::Rank(1); // or 14 depending on the hand
            } else {
                actualRank = Card::Rank(rank);
            }

            deck.push(Card(actualRank, static_cast<Card::Suit>(suit)));
        }
    }
}

    void shuffleDeck() {
        vector<Card> tempVector;

        // Converts deck, as a stack, to a deck, as a vector, for shuffling
        while (!deck.empty()) {
            tempVector.push_back(deck.top());
            deck.pop();
        }

        for (int i = 0; i < 7; i++) {
            // .begin() and .end() specify the range we would like to shuffle, in this case the entire deck.
            // mt19937 - Mersenne Twister Algorithm; random_device() - random number generator device, seeds engine mt19937
            shuffle(tempVector.begin(), tempVector.end(), mt19937(random_device()())); // random value obtained, immediately seed engine within a single line
        }

        for (const auto& card : tempVector) {
            deck.push(card);
        }
    }

    void cutDeck() { // Human error would entail approx halfway...should I include a random number generator within a valid range of "halfway" values
        // Linked list to represent deck
        DoublyLinkedList(Card) bottomHalf;
        DoublyLinkedList(Card) topHalf;
        int cutpoint = 26; // For 26 iterations

        for(int i = 0; i <= 25; i++) {
            topHalf.pushBack(deck.top());
            deck.pop();
        }

        for(int i = 0; i <= 25; i++) {
            bottomHalf.pushBack(deck.top());
            deck.pop();
        }

        for(int i = 0; i <= 25; i++) {
            deck.push(topHalf.tail->card);
            topHalf.tail = topHalf.tail->prev;
        }

        for(int i = 0; i <= 25; i++) {
            deck.push(bottomHalf.tail->card);
            bottomHalf.tail = bottomHalf.tail->prev;
        }

        topHalf.clear();
        bottomHalf.clear();
    }


    void burnCard() {
        deck.pop();
    }


    public:

    Deck() {
        InitializeDeck();
        shuffleDeck();
        cutDeck();
    }

    Card dealCard() {
        Card card = deck.top();
        deck.pop();
        return card;
    }

    bool isEmpty() {
        return deck.empty();
    }

    /*
    for each player
    ask action
    isbetmade
    Switch statements based on action 
    
    
    
    */


};

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
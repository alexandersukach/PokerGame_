#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;

class Player {
    private:
        string name;
        int balance, currentBet;
        bool isFolded, isComputerPlayer, bigBlind, smallBlind;
    
    public:
        Player();
        Player(const string& playerName, double startingBalance, bool isComputer);
        double getBalance() const;
        string getName() const;
        bool isComputer() const;
        void placeBet(double betPlaced); // setBalance and setCurrentBet
        void winBet(double betWon); // setBalance 
        //double getCurrentBet();
        double getCurrentBet() const;
        void raise(double raiseAmount); // 'setCurrentBet'
        void fold();
        bool hasFolded() const;
        
        void setBigBlind();
        bool isBigBlind();

        void setSmallBlind();
        bool isSmallBlind();
        // void cpuAction(bool isRaiseMade);

        bool operator==(const Player& other) const;



};


#endif // PLAYER_H
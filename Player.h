#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;

class Player {
    private:
        string name;
        int balance, currentBet;
        bool isFolded, isComputerPlayer;
    
    public:
        Player();
        Player(const string& playerName, double startingBalance);
        double getBalance() const;
        string getName() const;
        bool isComputer() const;
        void placeBet(double betPlaced); // setBalance and setCurrentBet
        void winBet(double betWon); // setBalance 
        int getCurrentBet();
        void raise(double raiseAmount); // setCurrentBet
        void fold();
        bool hasFolded();
        // void cpuAction(bool isRaiseMade);



};


#endif // PLAYER_H
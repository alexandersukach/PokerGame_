#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
    private:
        std::string name;
        int balance, currentBet;
        bool isBigBlind, isSmallBlind, isFolded, isComputerPlayer;
    
    public:
        Player();
        Player(const std::string& playerName, double startingBalance);
        

        double getBalance() const;
        bool isComputer() const;
        void setBalance(double bet);
        void winHand(double pot);
        void setCurrentBet(double betMade);
        int getCurrentBet();
        void placeBet(double betAmount);
        void raise(double raiseAmount);
        void fold();
        bool hasFolded();
        void bigBlindPayment();
        void smallBlindPayment();
        void setBigBlind();
        void setSmallBlind();
        // void cpuAction(bool isRaiseMade);



};


#endif // PLAYER_H
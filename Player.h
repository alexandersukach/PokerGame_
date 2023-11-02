#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
    private:
        std::string name;
        int balance, currentBet;
        bool isBigBlind, isSmallBlind, isFolded;
    
    public:
        Player(const std::string& playerName, int startingBalance);

        int getBalance() const;
        void winHand(int pot);
        void setCurrentBet(int betMade);
        // int getCurrentBet();
        void placeBet(int betAmount);
        void raise(int raiseAmount);
        void fold();
        void bigBlindPayment();
        void smallBlindPayment();
        void bigBlind();
        void smallBlind();
        // void cpuAction(bool isRaiseMade);



}


#endif // PLAYER_H
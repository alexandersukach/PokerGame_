#ifndef CARD_H
#define CARD_H

class Card {
    public:
        enum Rank { TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE }; // All possible ranks
        enum Suit { HEARTS, CLUBS, DIAMONDS, SPADES }; // All possible suits
        
        Card();
        Card(Rank r, Suit s);
        Rank getRank() const;
        Suit getSuit() const;
        void display() const;
        
    private: 
        Rank rank; // Type 'Rank' stores card rank within class
        Suit suit; // Type 'Suit' stores card suit within class
};
#endif // CARD_H

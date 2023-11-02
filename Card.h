#ifndef CARD_H
#define CARD_H


class Card {
    private:
        Rank rank;
        Suit suit;
    
    public:
        enum Rank { TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };
        enum Suit { HEARTS, CLUBS, DIAMONDS, SPADS };

        Card(Rank r, Suit s);

        Rank getRank() const;
        Suit getSuit() const;

        //void display() const;
};



#endif // CARD_H
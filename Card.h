#ifndef CARD_H
#define CARD_H


class Card {


    public:
        enum Rank { TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };
        enum Suit { HEARTS, CLUBS, DIAMONDS, SPADES };

        Card(Rank r, Suit s);

        Rank getRank() const;
        Suit getSuit() const;

        void display() const;
    private:
        Rank rank;
        Suit suit;

};



#endif // CARD_H
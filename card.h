#ifndef __CARD_H__
#define __CARD_H__

#include <iostream>
#include <string>

using namespace std;

class Card {
    private:
        char suit;
        string number;
        int value;
        bool isJoker;
    
    public:
        void setNumber(std::string s);
        Card(char suit, string number, int value);
        friend bool operator==(Card card1, Card card2);
        friend bool operator<(Card card1, Card card2);
        friend bool operator>(Card card1, Card card2);
        friend ostream& operator<<(ostream& os, Card card);
        bool getJoker();
        bool isEmpty();
        int getValue();
};

bool operator==(Card card1, Card card2);
bool operator<(Card card1, Card card2);
bool operator>(Card card1, Card card2);
ostream& operator<<(ostream& os, Card card);

#endif

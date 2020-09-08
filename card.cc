#include <iostream>
#include "card.h"

using namespace std;

Card::Card(char suit, string number, int value): suit{suit}, number{number}, value{value} {
    if (suit == 'J') {
        isJoker = true;
    } else {
        isJoker = false;
    }
}

bool Card::getJoker() {
    return isJoker;
}

bool Card::isEmpty() {
    if (suit == ' ')
        return true;
    return false;
}


int Card::getValue() {
    return value;
}

void Card::setNumber(std::string s) {
    number = s;

    value = 0;
    if (s == "A") {
        value = 1;
    } else if (s == "J") {
        value = 11;
    } else if (s == "Q") {
        value = 12;
    } else if (s == "K") {
        value = 13;
    } else {
        value = stoi(s);
    }
}

bool operator==(Card card1, Card card2) {
    if (card1.value != card2.value) {
        return false;
    }
    return true;
}

bool operator<(Card card1, Card card2) {
    if (card1.value < card2.value) {
        return true;
    }
    return false;

}

bool operator>(Card card1, Card card2) {
    if (card1 == card2) {
        return false;
    }
    if (card1 < card2) {
        return false;
    }
    return true;
}

std::ostream& operator<<(std::ostream& os, Card card) {
    if (card.isJoker) {
        os << card.number << "J";
        return os;
    }
    os << card.number << card.suit;
    return os;
}


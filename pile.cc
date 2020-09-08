#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "pile.h"

using namespace std;

const char SUITS[4] = {'S', 'H', 'C', 'D'};
const string NUM[13] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};

void Pile::addFullDeck() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            Card card(SUITS[i], NUM[j], j + 1);
            cardList.push_back(card);
        }
    }
    Card joker('J', "", 0);
    cardList.push_back(joker);
    cardList.push_back(joker);
}

void Pile::addToBack(Card card) {
    if (card.isEmpty())
        return;
    cardList.push_back(card);
}
void Pile::addToFront(Card card) {
    if (card.isEmpty())
        return;
    cardList.push_front(card);
}
Card Pile::drawFromBack() {
    if (cardList.size() > 0)
    {
        Card card = cardList.back();
        cardList.pop_back();
        return card;
    }
    return Card(' ', "", 0);
}
Card Pile::drawFromFront() {
    if (cardList.size() > 0)
    {
        Card card = cardList.front();
        cardList.pop_front();
        return card;
    }
    return Card(' ', "", 0);
}

void Pile::shuffleDeck() {
    vector<Card> vecCards(cardList.begin(), cardList.end());
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    shuffle(vecCards.begin(), vecCards.end(), default_random_engine(seed));

    copy(vecCards.begin(), vecCards.end(), cardList.begin());
}

int Pile::getSize() {
    return cardList.size();
}

Card & Pile::getFront() {
    return cardList.front();
}

Card Pile::drawTestCard()
{
    string cardValue;
    int cardIntValue;
    while (1)
    {
        bool isGood = false;
        cout << "Card Value?" << endl;
        cin >> cardValue;

        if (!cin.fail())
        {
            for (int i = 0; i < 13; i++) {
                if (cardValue == NUM[i] || cardValue == "Joker")
                {
                    isGood = true;
                    cardIntValue = i + 1;
                    break;
                }
            }
            if (isGood)
                break;
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    char cardSuit = ' ';

    if (cardValue != "Joker")
    {
    
        while (1)
        {

            bool isGood = false;
            cout << "Card Suit?" << endl;
            cin >> cardSuit;

            if (!cin.fail())
            {
                for (int i = 0; i < 4; i++) {
                    if (cardSuit == SUITS[i])
                    {
                        isGood = true;
                        break;
                    }
                }
                if (isGood)
                    break;
            }

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    Card oldCard = drawFromBack();

    if (cardValue == "Joker")
    {
        Card joker('J', "", 0);
        return joker;
    }
    return Card(cardSuit, cardValue, cardIntValue);
}

std::ostream& operator<<(std::ostream& os, Pile pile) {
    for (auto c : pile.cardList) {
        os << c << endl;
    }
    return os;
}


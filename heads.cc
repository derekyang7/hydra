#include "heads.h"

using namespace std;

int Heads::action(Card card, int move) {

    int validHeads = getValidHeadCount();
    if (move == 0)
    {
        if (validHeads < 2)
            return false;

    }
    int index = move - 1;

    Pile & theHead = headPiles[index];

    if (theHead.getFront() == card) {
        theHead.addToFront(card);
        return 2;
    }
    if (theHead.getFront().getValue() == 1) {
        theHead.addToFront(card);
        return 3;
    }
    if (theHead.getFront() > card) {
        theHead.addToFront(card);
        return 1;
    }

    return 0;
}

Pile& Heads::getFirstHead()
{
    for (unsigned i = 0; i < headPiles.size(); i++) {
        Pile& pile = headPiles[i];
        if (pile.getSize() > 0) {
            return pile;
        }
    }
    return headPiles[0];
}

void Heads::createHead(Card& card)
{
    if (card.getJoker())
        card.setNumber("2");

    Pile head;
    head.addToFront(card);
    headPiles.push_back(head);

}

bool Heads::isValidMove(Card card, int move)
{
    if (move == 0)
    {
        if (headPiles.size() > 1)
            return true;
        else
            return false;
    }

    if (move <= 0)
        return false;

    unsigned index = move - 1;
    if (index >= headPiles.size())
        return false;
    Pile& pile = headPiles[index];

    if (pile.getSize() == 0)
        return false;

    Card& headCard = pile.getFront();

    if (headCard.getValue() == 1)
        return true;
    
    if (card.getJoker() || card.getValue() == 1)
        return true;

    bool hasValidHead = false;
    for (unsigned i = 0; i < headPiles.size(); i++) {
        Pile& p = headPiles[i];
        if (p.getSize() > 0) {
            Card c = p.getFront();
            if (c.getValue() == 1 || c == card || c > card)
            {
                hasValidHead = true;
                break;
            }
        }
    }

    unsigned firstPileIndex = 0;
    for (unsigned i = 0; i < headPiles.size(); i++) {
        Pile& p = headPiles[i];
        if (p.getSize() > 0) {
            firstPileIndex = i;
            break;
        }
    }

    if (!hasValidHead && index != firstPileIndex)
        return false;

    if (hasValidHead && headCard < card)
        return false;

    return true;
}

int Heads::getValidHeadCount() {
    int counter = 0;
    for (unsigned i = 0; i < headPiles.size(); i++) {
        Pile& pile = headPiles[i];
        if (pile.getSize() > 0) {
            counter++;
        }
        
    }
    return counter;
}

ostream& operator<<(ostream& os, Heads heads) {
    os << "Heads:" << endl;
    for (unsigned i = 0; i < heads.headPiles.size(); i++) {
        Pile & pile = heads.headPiles[i];
        if (pile.getSize() > 0) {
            os << (i + 1) << ": " << pile.getFront() << " (" << pile.getSize() << ")" << endl;
        }
    }
    return os;
}

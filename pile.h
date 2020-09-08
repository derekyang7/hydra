#ifndef __PILE_H__
#define __PILE_H__

#include <list>
#include <iostream>
#include "card.h"

using namespace std;


class Pile {
    private:
        list<Card> cardList;
    
    public:
        void addFullDeck();
        void addToBack(Card card);
        void addToFront(Card card);
        Card drawFromBack();
        Card drawFromFront();
        void shuffleDeck();
        int getSize();
        Card & getFront();
        
        Card drawTestCard();

        friend std::ostream& operator<<(std::ostream& os, Pile pile);

};

std::ostream& operator<<(std::ostream& os, Pile pile);


#endif

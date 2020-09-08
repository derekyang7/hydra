#ifndef __HEADS_H__
#define __HEADS_H__

#include <vector>
#include "pile.h"

using namespace std;

class Heads {
    private:
        vector<Pile> headPiles;

    public:
        int action(Card card, int move);
        int getValidHeadCount();
        friend ostream& operator<<(ostream& os, Heads heads);
        Pile& getFirstHead();
        void createHead(Card& card);
        bool isValidMove(Card card, int move);
};

ostream& operator<<(ostream& os, Heads heads);

#endif

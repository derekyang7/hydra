#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <vector>
#include "pile.h"
#include "heads.h"

class Player {
    private:
        void cutOff(Heads& heads, bool test);
        int remaining;
    public:
        Player(int playerNum);
        Pile discardPile;
        Pile drawPile;
        Pile inHand;
        Pile reserve;
        void addToDrawPile(Card card);
        void drawCards(int numHeads);
        Card drawCard();
        bool play(Heads & heads, vector<Player> & players, bool test);
        //int getRemaining();
        int playerNum;
        friend ostream& operator<<(ostream& os, Player player);
        bool isEndTurn();
        bool isWinning();
        
};

ostream& operator<<(ostream& os, Player player);

#endif

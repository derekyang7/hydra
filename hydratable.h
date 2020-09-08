#ifndef __HYDRATABLE_H__
#define __HYDRATABLE_H__

#include <vector>
#include "pile.h"
#include "heads.h"
#include "player.h"

using namespace std;

class HydraTable {
    private:
        Pile allCards;
        vector<Player> allPlayers;
        Heads heads;


    public:
        void start(bool test);
        HydraTable(int numPlayers, int drawPileSize);
        static void displayPlayerMessage(vector <Player> & players);
};

#endif

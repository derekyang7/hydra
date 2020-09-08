#include "hydratable.h"

void HydraTable::displayPlayerMessage(vector <Player> & players) {
    cout << "Players:" << endl;
    for (unsigned i = 0; i < players.size(); i++) {
        cout << players[i];
     }

    cout << endl;
}

void HydraTable::start(bool test) {
    /*
    for (int i = 0; i < allPlayers.size(); i++) {
        Player player = allPlayers[i];

        cout << player.drawPile;

    }
    */

   while (1) {
       for (unsigned i = 0; i < allPlayers.size(); i++) {
           Player & player = allPlayers[i];
           bool win = player.play(heads, allPlayers, test);

           if (win) {
               cout << "Player " << (i + 1) << " wins!" << endl;
               return;
           }
            
       }
   }
}

HydraTable::HydraTable(int numPlayers, int drawPileSize) {
    for (int i = 0; i < numPlayers; i++) {
        allCards.addFullDeck();
    }

    allCards.shuffleDeck();

    for (int i = 0; i < numPlayers; i++) {
        Player player(i + 1);
        for (int j = 0; j < drawPileSize; j++) {
            Card card = allCards.drawFromBack();
            player.addToDrawPile(card);
        }

        allPlayers.push_back(player);

    }
}

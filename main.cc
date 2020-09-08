#include "hydratable.h"

int main(int argc, char* argv[]) {

    bool test = false;
    int drawPileSize = 54;

    // For -testing argument:
    if (argc >= 2)
    {
        for (int i = 1; i < argc; i++)
        {
            string argv1 = argv[i];
            if (argv1 == "-testing") {
                test = true;
            }

            // -drawPileSize=<NUMBER>, replace <NUMBER> with desired draw pile size for each player
            if (argv1.size() > 14 && argv1.substr(0, 14) == "-drawPileSize=")
            {
                string s = argv1.substr(14);
                try
                {
                    drawPileSize = stoi(s);
                }
                catch(...)
                {

                }
            }
        }
    }

    int numPlayers = 0;
    do
    {
        cout << "How many players?" << endl;
        cin >> numPlayers;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
    } while (numPlayers < 2);

    HydraTable table(numPlayers, drawPileSize);

    table.start(test);
}

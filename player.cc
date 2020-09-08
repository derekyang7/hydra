#include "player.h"
#include "hydratable.h"

 Player::Player(int playerNum): playerNum{playerNum} {
     remaining = -1;
 }

void Player::cutOff(Heads& heads, bool test) {
    //Card card = drawPile.drawFromBack();
    //discardPile.addToBack(card);
    //Card rCard = reserve.drawFromBack();
    //discardPile.addToBack(rCard);
    
    //move every head in the oldest head, face down, into the discard pile
    //with the top two cards from the player's draw pile (reshuffling the discard pile if necessary), create two new
    //heads by placing the two cards, face up, as two new piles. Any jokers placed in this manner are given the value 2.
    
    Pile& oldestHead = heads.getFirstHead();

    int size = oldestHead.getSize();

    for(int i = 0; i < size; i++)
    {
        Card card = oldestHead.drawFromFront();
        discardPile.addToBack(card);
    }

    if (test)
    {
        cout << "Enter two cards for two new heads:" << endl;
        Card card1 = drawPile.drawTestCard();
        heads.createHead(card1);
        Card card2 = drawPile.drawTestCard();
        heads.createHead(card2);
    }
    else
    {
        Card card1 = drawCard();
        if (!card1.isEmpty())
        {
            heads.createHead(card1);
        }
        Card card2 = drawCard();
        if (!card2.isEmpty())
        {
            heads.createHead(card2);
        }
    }
}

void Player::addToDrawPile(Card card) {
    drawPile.addToBack(card);   
}

Card Player::drawCard() {
    if (drawPile.getSize() == 0 && discardPile.getSize() == 0)
    {
        if (reserve.getSize() > 0)
        {
            Card resCard = reserve.drawFromBack();
            return resCard;
        }
        return Card(' ', "", 0);
    }

    if (drawPile.getSize() == 0)
    {
        discardPile.shuffleDeck();

        int size = discardPile.getSize();
        for (int i = 0; i < size; i++)
        {
            Card card = discardPile.drawFromBack();
            drawPile.addToFront(card);
        }
    }
  
    Card newCard = drawPile.drawFromBack();
    remaining--;
    return newCard;

}

void Player::drawCards(int numCards) {
    for (int i  = 0; i < numCards; i++) {
        Card card = drawCard();
        if(!card.isEmpty())
            inHand.addToBack(card);
    }
}

bool Player::play(Heads & heads, vector<Player> & players, bool test) {
        int numHeads = heads.getValidHeadCount();
        if (numHeads == 0) {
            if (test)
            {
                cout << "Enter card for first head:" << endl;
                Card card = drawPile.drawTestCard();
                inHand.addToBack(card);
            }
            else
            {
                drawCards(1);
            }
            Card card = inHand.drawFromBack();
            heads.createHead(card);
            cout << heads << endl;
            HydraTable::displayPlayerMessage(players);
            return false;
        }
        std::cin.ignore(1000, '\n');
        do
        {
            cout << "Player " << playerNum << ", it is your turn." << endl;
            //cout << '\n' << "Press a key to continue...";
        } while (cin.get() != '\n');


        //drawCards(numHeads);
        remaining = numHeads;

        while (!isEndTurn() && !isWinning()) {
            
            drawCards(1);
            
            cout << heads << endl;
            HydraTable::displayPlayerMessage(players);

            Card card = (test) ? inHand.drawTestCard() :  inHand.drawFromBack();

            int move;
            do
            {
                if (card.getJoker())
                    cout << "Player " << playerNum << ", you are holding a Joker. Your move?" << endl;
                else
                    cout << "Player " << playerNum << ", you are holding a " << card << ". Your move?" << endl;
                
                cin >> move;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
            } while (!heads.isValidMove(card, move));

            if (move == 0) {
                if (reserve.getSize() == 0) {
                    reserve.addToBack(card);
                }
                else {
                    Card temp = reserve.drawFromBack();
                    reserve.addToBack(card);
                    drawPile.addToBack(temp);
                    remaining++;
                }
                continue;
            }
            
            if (card.getJoker()) {
                do
                {
                    cout << "Joker value?" << endl;
                    string number;
                    cin >> number;
                    if (!cin.fail())
                    {
                        card.setNumber(number);
                        if (card.getValue() > 0)
                        {
                            break;
                        }
                    }
                    cin.clear();
                    cin.ignore(10000, '\n');

                } while (1);
            }
            
            cout << endl;


            
            int result = heads.action(card, move);
            bool endTurn = false;
            switch (result) {
                case 0:
                    discardPile.addToBack(card);
                    cutOff(heads, test);
                    endTurn = true;
                    break;
                case 1:
                    endTurn = false;
                    break;
                case 2:
                    endTurn = true;
                    break;
                case 3:
                    endTurn = false;
                    break;
            }

            if (endTurn)
            {
                break;
            }
        }
        
        if (isWinning()) {
            return true;
        }

        if (reserve.getSize() > 0)
        {
            Card rCard = reserve.drawFromBack();
            discardPile.addToBack(rCard);
        }

        int size = inHand.getSize();
        for (int n = 0; n < size; n++)
        {
            Card nCard = inHand.drawFromBack();
            discardPile.addToBack(nCard);
        }
        
        remaining = -1;

        cout << heads << endl;
        HydraTable::displayPlayerMessage(players);
        
        return false;
}

ostream& operator<<(ostream& os, Player player) {
    if (player.remaining >= 0) {
        cout << "Player " << player.playerNum << ": " << (player.drawPile.getSize() + player.discardPile.getSize()) << " (" 
        << player.drawPile.getSize() << " draw, " << player.discardPile.getSize() << " discard) + 1 in hand, " 
        << player.remaining << " remaining, " << player.reserve.getSize() << " in reserve" << endl;
    } else {
        cout << "Player " << player.playerNum << ": " << (player.drawPile.getSize() + player.discardPile.getSize()) << " (" 
        << player.drawPile.getSize() << " draw, " << player.discardPile.getSize() << " discard)" << endl;
    }
    return os;
}

bool Player::isEndTurn() {
    if (remaining <= 0 && inHand.getSize() == 0) {
        return true;
    } else {
        return false;
    }
}

bool Player::isWinning() {
    if (inHand.getSize() == 0 && drawPile.getSize() == 0 && discardPile.getSize() == 0 && reserve.getSize() == 0) {
        return true;
    }
    return false;
}

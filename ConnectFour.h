#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H
#include "Player.h"
using namespace std;

/*
* Primary class for the Connect Four game.
* It manages each game turn and checks for win conditions after each move.
*/
class ConnectFour {
    public:
        ConnectFour(Player* p1, Player* p2);
        void PlayGame();
    private:
        GameBoard board;
        Player* player1;
        Player* player2;
};
#endif
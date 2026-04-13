#ifndef PLAYERS_H
#define PLAYERS_H
#include "GameBoard.h"
using namespace std;

/*
* Base class for players in the Connect Four game. 
*/
class Player {
    public:
        Player(char symbol);
        virtual int MakeNextMove(GameBoard& board);
        char GetPlayerSymbol() const;
    protected:
        char currentPlayer;
};
#endif
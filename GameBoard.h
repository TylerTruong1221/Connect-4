#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>
using namespace std;

/* 
* Creates the board for the game and contains functions to manipulate the board, 
* such as checking for valid moves, making moves, checking for wins, and printing the board.
*/
class GameBoard {
    public:
        GameBoard();
        GameBoard(const GameBoard& origGameBoard);
        bool ValidMove(int col);
        bool Move(int col, char player);
        bool CheckWin(char player);
        bool FullBoard();
        void PrintBoard() const;
        vector<int> GetValidLocations();
        char GetSpace(int row, int col);
        int GetNextOpenRow(int col);
        void PlacePiece(int row, int col, char player);

    private:
        vector<vector<char>> board;
        const int ROWS = 6;
        const int COLS = 7;
};

#endif
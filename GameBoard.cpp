#include "GameBoard.h"
#include <vector>
#include <iostream>
using namespace std;

// Initializes the game board with empty spaces
GameBoard::GameBoard() {
    board.resize(ROWS, vector<char>(COLS, ' '));
}

// Checks if a move is valid
bool GameBoard::ValidMove(int col) {
    return col >= 0 && col < COLS && board[0][col] == ' ';
}

// Makes a move for the player in the specified column
bool GameBoard::Move(int col, char player) {
    bool moveMade = false;
    if (!ValidMove(col)) { 
        return false;
    }
    for (int i = ROWS - 1; i >= 0; i--) {
        if (board[i][col] == ' ') {
            board[i][col] = player;
            moveMade = true;
            break;
        }
    }
    return moveMade;
}

// Checks if the specified player has won the game
bool GameBoard::CheckWin(char player) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            // Check if each cell contains the player's symbol
            if (board[i][j] == player) {
                // Check horizontal
                if (j <= COLS - 4 && board[i][j + 1] == player && board[i][j + 2] == player && board[i][j + 3] == player) {
                    return true;
                }
                // Check vertical
                if (i <= ROWS - 4 && board[i + 1][j] == player && board[i + 2][j] == player && board[i + 3][j] == player) {
                    return true;
                }
                // Check diagonal down-right
                if (i <= ROWS - 4 && j <= COLS - 4 && board[i + 1][j + 1] == player && board[i + 2][j + 2] == player && board[i + 3][j + 3] == player) {
                    return true;
                }
                // Check diagonal down-left
                if (i <= ROWS - 4 && j >= 3 && board[i + 1][j - 1] == player && board[i + 2][j - 2] == player && board[i + 3][j - 3] == player) {
                    return true;
                }
            }
        }
    }
    return false;
}

// Checks if the board is full
bool GameBoard::FullBoard() {
    bool isFull = true;
    for (int i = 0; i < COLS; i++) {
        if (board[0][i] == ' ') {
            isFull = false;
        }
    }
    return isFull;
}

// Prints the board
void GameBoard::PrintBoard() const {
    cout << endl;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cout << "|" << board[i][j] ;
        }
        cout << "|" << endl;
    }
    cout << " 1 2 3 4 5 6 7 " << endl << endl;
}
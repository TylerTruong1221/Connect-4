#include "ConnectFour.h"
#include <iostream>
using namespace std;

// Constructor to initialize the game with two players
ConnectFour::ConnectFour(Player* p1, Player* p2) : player1(p1), player2(p2), winner('D') {}

// Game loop
void ConnectFour::PlayGame() {
    Player* currentPlayer = player1;
    winner = 'D';
    while (true) {
        board.PrintBoard();
        int move = currentPlayer->MakeNextMove(board);

        // Check if the move is valid
        if (!board.Move(move, currentPlayer->GetPlayerSymbol())) {
            cout << "Invalid move, try again." << endl;
            continue;
        }

        // Check win
        if (board.CheckWin(currentPlayer->GetPlayerSymbol())) {
            board.PrintBoard();
            cout << "Player " << currentPlayer->GetPlayerSymbol() << " wins!" << endl;
            winner = currentPlayer->GetPlayerSymbol();
            break;
        }

        // Check draw
        if (board.FullBoard()) {
            board.PrintBoard();
            cout << "It's a draw!" << endl;
            winner = 'D';
            break;
        }

        // Switch players
        currentPlayer = (currentPlayer == player1) ? player2 : player1;
    }
}
//Get winner score
char ConnectFour::GetWinner() const {
    return winner;
}

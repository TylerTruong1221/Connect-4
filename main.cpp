#include <iostream>
#include <vector>
#include <ctime>
#include "ConnectFour.h"
using namespace std;

// Logic for a human player
class HumanPlayer : public Player {
public:
    HumanPlayer(char t) : Player(t) {}

    int MakeNextMove(GameBoard& board) override {
        int col;
        cout << "Enter column (1-7): ";
        cin >> col;
        return col - 1;
    }
};

// Logic for an AI player
class AIPlayer : public Player {
public:
    AIPlayer(char t) : Player(t) {}

    int MakeNextMove(GameBoard& board) override {
        int col = rand() % 7;
        while (!board.ValidMove(col)) {
            col = rand() % 7;
        }

        cout << "AI chooses column: " << col + 1 << endl;
        return col;
    }
};

int main() {
    srand(time(0));
    char symbol;

    cout << "Welcome to Connect Four!" << endl;
    cout << "Choose symbol to play (X/O): ";
    cin >> symbol;

    while (symbol != 'X' && symbol != 'O') {
        cout << "Invalid symbol. Please choose X or O: ";
        cin >> symbol;
    }

    // Create players and start the game
    HumanPlayer human(symbol);
    AIPlayer ai(symbol == 'X' ? 'O' : 'X');

    // Player X will always go first
    if (symbol == 'X') {
        ConnectFour game(&human, &ai);
        game.PlayGame();
    } else {
        ConnectFour game(&ai, &human);
        game.PlayGame();
    }
    
    return 0;
}
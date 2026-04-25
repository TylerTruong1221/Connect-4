#include <iostream>
#include <vector>
#include <ctime>
#include <limits>
#include <algorithm>
#include "ConnectFour.h"
using namespace std;

const int MAX = std::numeric_limits<int>::max();
const int MIN = std::numeric_limits<int>::min();
const int WINDOW_COUNT = 4;
const int ROWS = 6;
const int COLS = 7;

//Class to be able to return both board column and minimax score from MiniMax function
class MiniMaxOutput {
	public:
		MiniMaxOutput() {
			col = -1;
			score = 0;
		}
		MiniMaxOutput(int column, int miniMaxScore) {
			col = column;
			score = miniMaxScore;
		}
		void SetColumn(int column) {
			col = column;
		}
		void SetScore(int miniMaxScore) {
			score = miniMaxScore;
		}
		int GetColumn() {
			return col;
		}
		int GetScore() {
			return score;
		}
	private:
		int col;
		int score;
};

//Check if game has terminated
bool IsTerminalNode(GameBoard board, Player* p1, Player* p2) {

	return board.CheckWin(p1->GetPlayerSymbol()) || board.CheckWin(p2->GetPlayerSymbol()) || board.FullBoard();
}

//Evaluate the score each space of selected window
int EvaluateWindow(vector<char> window, Player* aiPlayer, Player* humanPlayer, char player) {
	int score = 0;
	char oppPlayer = humanPlayer->GetPlayerSymbol();
	if (player == humanPlayer->GetPlayerSymbol()) {
		oppPlayer = aiPlayer->GetPlayerSymbol();
	}

	int playerCount = 0;
	int emptyCount = 0;
	int oppCount = 0;
	for (size_t i = 0 ; i < window.size() ; i++) {
		if (window.at(i) == player) {
			playerCount++;
		} else if (window.at(i) == ' ') {
			emptyCount++;
		} else if (window.at(i) == oppPlayer) {
			oppCount++;
		}
	}

	if (playerCount == 4) {
		score += 100;
	} else if (playerCount == 3 && emptyCount == 1) {
		score += 5;
	} else if (playerCount == 2 && emptyCount == 2) {
		score += 2;
	}

	if (oppCount == 3 && emptyCount == 1) {
		score -= 4;
	}

	return score;

}

//Create score for each space to determine which move maximizes success and minimizes opponent's goal to have player lose
int ScorePosition(GameBoard board, Player* aiPlayer, Player* humanPlayer, char player) {
	int score = 0;
	//score centre column
	int centerCount = 0;
	int centerColIndex = COLS / 2;
	vector<char> centreVector;
	for (int i = 0 ; i < ROWS ; i++) {
		char value = board.GetSpace(i, centerColIndex);
		centreVector.push_back(value);
	}

	for (size_t i = 0 ; i < centreVector.size() ; i++) {
		if (centreVector.at(i) == player) {
			centerCount++;
		}
	}
	score += centerCount * 3;

	//score horizontal positions
	for (int i = 0 ; i < ROWS ; i++) {
		vector<char> rowVector;
		for (int j = 0 ; j < COLS ; j++) {
			char value = board.GetSpace(i, j);
			rowVector.push_back(value);
		}

		for (int j = 0 ; j < COLS - 3 ; j++) {
			vector<char> window;
			for (int k = 0 ; k < WINDOW_COUNT ; k++) {
				window.push_back(rowVector.at(j + k));
			}
			score += EvaluateWindow(window, aiPlayer, humanPlayer, player);
		}
	}

	//score vertical positions
    for (int i = 0 ; i < COLS ; i++) {
        vector <char> colVector;
        for (int j = 0 ; j < ROWS ; j++) {
            char value = board.GetSpace(j, i);
            colVector.push_back(value);
        }

        for (int j = 0 ; j < ROWS - 3 ; j++) {
			vector<char> window;
			for (int k = 0 ; k < WINDOW_COUNT ; k++) {
				window.push_back(colVector.at(j + k));
			}
			score += EvaluateWindow(window, aiPlayer, humanPlayer, player);
        }
    }

	//score positive diagonals
	for (int i = 0 ; i < ROWS - 3 ; i++) {
		for (int j = 0 ; j < COLS - 3 ; j++) {
			vector<char> window;
			for (int k = 0 ; k < WINDOW_COUNT ; k++) {
				char value = board.GetSpace(i + k, j + k);
				window.push_back(value);
			}
			score += EvaluateWindow(window, aiPlayer, humanPlayer, player);
		}
	}

	for (int i = 0 ; i < ROWS - 3 ; i++) {
		for (int j = 0 ; j < COLS - 3 ; j++) {
			vector<char> window;
			for (int k = 0 ; k < WINDOW_COUNT ; k++) {
				char value = board.GetSpace(i + 3 - k, j + k);
				window.push_back(value);
			}
			score += EvaluateWindow(window, aiPlayer, humanPlayer, player);
		}
	}

	return score;
}

//Utilizing MiniMax algorithm with alpha-beta pruning for AI opponent to determine best next move
MiniMaxOutput MiniMax(GameBoard board, int depth, int alpha, int beta, bool maximizingPlayer, Player* p1, Player* p2, char player) {
	Player* aiPlayer = p2;
	Player* humanPlayer = p1;
	vector<int> validLocations = board.GetValidLocations();
	bool isTerminal = IsTerminalNode(board, p1, p2);
	if (depth == 0 || isTerminal) {
		if (isTerminal) {
			if (board.CheckWin(aiPlayer->GetPlayerSymbol())) {
				return MiniMaxOutput(-1, MAX);
			} else if (board.CheckWin(humanPlayer->GetPlayerSymbol())) {
				return MiniMaxOutput(-1, MIN);
			} else {
				return MiniMaxOutput();
			}
		} else {
			return MiniMaxOutput(-1, ScorePosition(board, aiPlayer, humanPlayer, aiPlayer->GetPlayerSymbol()));
		}
	}

	//maximize score if maximizing player's turn
	if (maximizingPlayer) {
		int value = MIN;
		int col = validLocations.at(rand() % validLocations.size());
		for (size_t i = 0 ; i < validLocations.size() ; i++) {
			int column = validLocations.at(i);
			int row = board.GetNextOpenRow(column);
			GameBoard boardCopy = board;
			boardCopy.PlacePiece(row, column, aiPlayer->GetPlayerSymbol());
			int newScore = MiniMax(boardCopy, depth - 1, alpha, beta, false, p1, p2, player).GetScore();

			if (newScore > value) {
				value = newScore;
				col = column;
			}

			alpha = max(alpha, value);

			if (alpha >= beta) {
				break;
			}
		}

		return MiniMaxOutput(col, value);
	//minimize score if minimizing player's turn
	} else {
		int value = MAX;
		int col = validLocations.at(rand() % validLocations.size());
		for (size_t i = 0 ; i < validLocations.size() ; i++){
			int column = validLocations.at(i);
			int row = board.GetNextOpenRow(column);
			GameBoard boardCopy = board;
			boardCopy.PlacePiece(row, column, humanPlayer->GetPlayerSymbol());
			int newScore = MiniMax(boardCopy, depth - 1, alpha, beta, true, p1, p2, player).GetScore();

			if (newScore < value) {
				value = newScore;
				col = column;
			}

			beta = min(beta, value);

			if (alpha >= beta) {
				break;
			}

		}

		return MiniMaxOutput(col, value);
	}
}

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
private:
	Player* humanPlayer;
public:
    AIPlayer(char t) : Player(t) {
		humanPlayer = new Player(t == 'X' ? 'O' : 'X');
	}

	~AIPlayer() {
		delete humanPlayer;
	}

    int MakeNextMove(GameBoard& board) override {
		MiniMaxOutput bestMove = MiniMax(board, 3, MIN, MAX, true, humanPlayer, this, currentPlayer);
		int col = bestMove.GetColumn();
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
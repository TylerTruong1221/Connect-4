#include "Player.h"
#include <iostream>
using namespace std;

// Constructor to initialize the player's symbol
Player::Player(char symbol) : currentPlayer(symbol) {}

int Player::MakeNextMove(GameBoard& board) {
    return 0;
}

// Returns the player's symbol
char Player::GetPlayerSymbol() const {
    return currentPlayer;
}

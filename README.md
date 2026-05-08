
## About The Project

Our group designed a text-based Connect 4 game that can be played single-player against an AI by prompting the player for moves and displaying the resulting board state. The game has all of the same rules and gameplay mechanics as regular Connect 4. The AI moves based on the state of the board and adapts to what the human player does.

## How To Run The Program

### Clone The Repository

Run the following commands to clone the repository and enter the directory
```bash
git clone https://github.com/TylerTruong1221/Connect-4.git
cd Connect-4
```

### Compile And Run

A C++ compatible compiler is required for compiling the program, such as g++.
For g++, run the following command

```bash
g++ main.cpp GameBoard.cpp Player.cpp ConnectFour.cpp -o ConnectFour
./ConnectFour
```

## How To Play

After running the program, the player begins by choosing a symbol to play as, X or O. The AI will play as the other symbol and player X will move first. 

A board with 7 columns and 6 rows will be displayed. Choosing one of the columns will drop the player's symbol to the bottom of the chosen column. The human player will take turns with the AI to drop symbols onto the board until one player matches 4 symbols in a row vertically, horizontally, or diagonally, thus winning the game.

## Classes And Structure Of Code

The project uses object-oriented programming concepts such as inheritance, polymorphism, encapsulation, and abstraction to create the players and gameplay.

### Player

The Player class serves as the base class for players in the game. It is primarily used to organize each player in terms of what symbol each player has and what moves they are making. It features the MakeNextMove function to be overridden. This allows for polymorphism and inheritance so that the human and AI players can implement the function differently. 

### GameBoard

The GameBoard class manages the board that the Connect 4 game is played on using a 2D vector of characters. It contains logic essential for receiving moves and updating the board as well as logic to check for wins and if the board is full (a tie). It also includes functions such as GetNextOpenRow that the AI uses because it is related to the board management.

### ConnectFour 

The ConnectFour class manages the actual playing of the game. It determines which player is making a move, makes moves based on input, and switches them between rounds. It also works with the GameBoard class to detect wins or draws.

### MiniMaxOutput

The MiniMaxOutput helper class is used by the AI player to determine the best move it has using a MiniMax algorithm. By assigning a score to each board space using the ScorePosition function, it uses the MiniMax functions to do a depth-first search of its possible moves, scoring each outcome. The algorithm uses Alpha-Beta pruning to reduce unnecessary searches and how many outcomes it has to check.
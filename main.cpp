#include <iostream>
#include <vector>

#include "regularBoard.cpp"
#include "input123.cpp"

// this is a concept first described to me by Taahaa Qazi. We have a tictactoe board which has tictactoe boards as element.
// The goal of the game is to try and win the 'outer' game of tictactoe, but the only way to do this is to win the regular games of tictactoe.
// where you place your counters decides which is the next board you play on. 
// For example, if you place your counter on the top middle of the board you are playing on, then the next move is in the top middle
// If the board you would have moved to has already been won, then you get a free choice of where to place your next counter


//this is our big board class
// variables are winner and the board state
// class methods are
// makeMove -  allows player to make a move
// printBoard - which prints what is on one of the regular tictactoe boards
// printBigBoard - which prints the current state of the big board
// checkWinner - checks if anyone has won
class bigBoard {
private:
    std::vector<std::vector<board>> boardState;
public:
    std::string winner = " "; 
// constructor creates a full board with a regular tictactoe board as its elements
    bigBoard() {
        board board1,board2,board3,board4,board5,board6,board7,board8,board9;
        boardState = {{board1,board2,board3},{board4,board5,board6},{board7,board8,board9}};
    }
    void makeMove(std::string player, int& row, int& column);
    void printBoard();
    void printBigBoard(); 
    void checkWinner();
};

// make a move on one of the boards as long as it is valid
// needs to return new row and column for the next move
void bigBoard::makeMove(std::string player, int& row, int& column) {
    std::vector<int> rowColumn;
    // things to consider:
    // first turn player gets free choice.
    if (row==100 && column==100) {
        int freeRow;
        int freeColumn;
        //take input for what board to make a move on - do not call row and column variables row and column
        //take input for freeRow and freeColumn until it is 1,2,3
        std::cout << "First move so you get a free choice of board\n";
        input123(freeRow,freeColumn);
        
        // then make the move and check if that board is won (so then in subsequent moves we get the free move condition)
        rowColumn=(boardState[freeRow-1][freeColumn-1]).makeMove(player);
        // cannot win either game or board off first term so don't botther checking if game or board is won

        // make the next row these values to force next player to make move in the correct board
        row=rowColumn[0];
        column=rowColumn[1];
    }

    // if board has been won, player gets free choice of where to put counter
    // needs to be separate from first turn statement as clearly boardState[100][100] is out of array bounds and leads to undefined behaviour
    else if ((boardState[row-1][column-1]).winner!= " ") {
        int freeRow;
        int freeColumn;
        //take input for what board to make a move on - do not call row and column variables row and column
        //take input for freeRow and freeColumn until it is 1,2,3       
        std::cout << "This board has already been won so you get a free choice of board";
        // take input for board to play on 
        // make sure that this isn't a board that has been won
        
        input123(freeRow,freeColumn);

        // make the move and check if board is won (so in future moves we get free move and on big board we can see this)
        rowColumn=(boardState[freeRow-1][freeColumn-1]).makeMove(player);
        (boardState[freeRow-1][freeColumn-1]).checkWinner();

        //check if game is won
        checkWinner();
        // make the next row these values to force next player to make move in the correct board
        row=rowColumn[0];
        column=rowColumn[1];
    }

    // allows player to make a move as long as it is valid on the board
    // and is the board that the previous player forced this move to be on
    else {
        //make move and check winner of board
        rowColumn=(boardState[row-1][column-1]).makeMove(player);
        (boardState[row-1][column-1]).checkWinner();

        //check if game is won
        checkWinner();
        row=rowColumn[0];
        column=rowColumn[1];
    }
}

// this function allows a player to view one of the regular boards in the big board
// take input for row column until they are both 1,2,3
// then print the corresponding board
void bigBoard::printBoard() {
    int row;
    int column;

    //take input for row and column until it is 1,2,3
    input123(row,column);
    
    // then print the correct board
    (boardState[row-1][column-1]).printBoard();
}

//prints the big board structure
void bigBoard::printBigBoard() {
    std::cout << (boardState[0][0]).winner << "|" << (boardState[0][1]).winner << "|"<< (boardState[0][2]).winner << "\n";
    std::cout << "-----\n";
    std::cout << (boardState[1][0]).winner << "|" << (boardState[1][1]).winner << "|"<< (boardState[1][2]).winner << "\n";
    std::cout << "-----\n";
    std::cout << (boardState[2][0]).winner << "|" << (boardState[2][1]).winner << "|"<< (boardState[2][2]).winner << "\n";
}

// checks if anyone has won the game through checking what combination of regular boards has been won
void bigBoard::checkWinner() {
    if (boardState[0][0].winner==boardState[1][0].winner && boardState[0][0].winner==boardState[2][0].winner && !(boardState[0][0].winner=="No Winner")) {
        winner=boardState[0][0].winner;
    }
    else if (boardState[0][0].winner==boardState[1][1].winner && boardState[0][0].winner==boardState[2][2].winner && !(boardState[0][0].winner=="No Winner")) {
        winner=boardState[0][0].winner;
    }
    else if (boardState[0][0].winner==boardState[0][1].winner && boardState[0][0].winner==boardState[0][2].winner && !(boardState[0][0].winner=="No Winner")) {
        winner=boardState[0][0].winner;
    }
    else if (boardState[0][1].winner==boardState[1][1].winner && boardState[0][1].winner==boardState[2][1].winner && !(boardState[0][1].winner=="No Winner")) {
        winner=boardState[0][1].winner;
    }
    else if (boardState[0][2].winner==boardState[1][1].winner && boardState[0][2].winner==boardState[2][0].winner && !(boardState[0][2].winner=="No Winner")) {
        winner=boardState[0][2].winner;
    }
    else if (boardState[0][2].winner==boardState[1][2].winner && boardState[0][2].winner==boardState[2][2].winner && !(boardState[0][2].winner=="No Winner")) {
        winner=boardState[0][2].winner;
    }
    else if (boardState[1][0].winner==boardState[1][1].winner && boardState[1][0].winner==boardState[1][2].winner && !(boardState[1][0].winner=="No Winner")) {
        winner=boardState[1][0].winner; 
    }
    else if (boardState[2][0].winner==boardState[2][1].winner && boardState[2][0].winner==boardState[2][2].winner && !(boardState[2][0].winner=="No Winner")) {
        winner=boardState[2][0].winner;
    }
}

int main() {
    /*rules: tictactoe board consisting of tictactoe boards
    place counters on big board winning the regular tictactoe boards
    where ever you place a counter on the regular tictactoe board you will get sent to the corresponding board on the big tictactoe board to make a move
    if the board is already won then you get a free move */
    bigBoard board1;

    //randomises who starts the game - this will be flipped immediatedly when the game starts but will have the same effect of randomising the starting player
    std::string currentPlayer;
    srand(time(0));
    int coinToss = rand() % 2;
    if (coinToss==0) {
        currentPlayer="o";
    }
    else {
        currentPlayer="x";
    }

    // special cases - for the first move - if we put these into the make move function then player is allowed to make a move on any board
    int nextRow=100;
    int nextcolumn=100;

    //while no one has won, play the game
    while (board1.winner==" ")  {
        // swap players around each turn
        if (currentPlayer=="o") {
            currentPlayer="x";
        } 
        else if (currentPlayer=="x") {
            currentPlayer="o";
        }
        //this is a player's turn
        // player can check big board state, the state of one of the boards or make a move
        std::cout << "Next move: " << currentPlayer << "\n";
        bool moveFinished=false;
        while (moveFinished==false) {

            // take an option from player until it is valid
            int option;
            std::cout << "Please select an option: \n1. Make a move \n2. View the whole board \n3. View a board \n4. Rules\n"; 
            while (!(std::cin>>option)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Please type 1,2,3 or 4\n";
            }
            //only 1,2,3 allowed as inputs
            if (option==1) {
                board1.makeMove(currentPlayer, nextRow, nextcolumn);
                moveFinished=true;
            }
            else if (option==2) {
                board1.printBigBoard();
            }
            else if (option==3) {
                board1.printBoard();
            } 
            else if (option==4) {
                std::cout << "This section is still being built\n";
            }
            else {
                std::cout << "That is not a valid option \n";
            }
        }
    }
    
    //once game has been won, congratulate player or state draw has been achieved.
    board1.printBigBoard();
    if (board1.winner!="No Winner") {
        std::cout << "Congratulations to " << currentPlayer << "\n";
    }
    else {
        std::cout << "Draw\n";
    }
    return 0;
}

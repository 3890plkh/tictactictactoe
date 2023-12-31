#include <iostream>
#include <vector>
#include <string>

#include "regularBoard.h"
#include "input123.h"

//this is our big board class
// variables are winner and the board state and boardFinished
// class methods are
// makeMove -  allows player to make a move
// printBigBoard - which prints the current state of the big board
// checkWinner - checks if anyone has won
// isBoardFinished - checks if we have no available moves left, if so game is a draw
class bigBoard {
private:
    std::vector<std::vector<board>> boardState;
public:
    std::string winner = " "; 
    bool boardFinished=false;
// constructor creates a full board with a regular tictactoe board as its elements
    bigBoard() {
        board board1,board2,board3,board4,board5,board6,board7,board8,board9;
        boardState = {{board1,board2,board3},{board4,board5,board6},{board7,board8,board9}};
    }
    void makeMove(std::string player, int& row, int& column);
    void printBigBoard(); 
    void checkWinner();
    void isBoardFinished();
};

// make a move on one of the boards as long as it is valid
// needs to return new row and column for the next move
void bigBoard::makeMove(std::string player, int& row, int& column) {
    std::vector<int> rowColumn;

    // things to consider:
    // first turn player gets free choice of which board to play on
    if (row==100 && column==100) {
        int freeRow;
        int freeColumn;
        //take input for what board to make a move on
        //take input for freeRow and freeColumn until it is 1,2,3
        std::cout << "First move so you get a free choice of board\n";
        input123(freeRow,freeColumn);
        
        // then make the move and check if that board is won (so then in subsequent moves we get the free move condition)
        rowColumn=(boardState[freeRow-1][freeColumn-1]).makeMove(player);
        // cannot win either game or board off first term so don't bother checking if game or board is won or drawn

        // make the next row these values to force next player to make move in the correct board
        row=rowColumn[0];
        column=rowColumn[1];
        return;
    }

    // if board has been won, player gets free choice of where to put counter
    // needs to be separate from first turn statement as clearly boardState[100][100] is out of array bounds and leads to undefined behaviour
    else if ((boardState[row-1][column-1]).boardFinished==true) {   
        std::cout << "This board has already been won or drawn so you get a free choice of board\n";

        // take input for board to play on 
        // make sure that this isn't a board that has been won or drawn
        bool choiceValid=false;
        while (choiceValid==false) {
            //take input for row and column until it is 1,2,3 
             input123(row,column);
             //if game hasn't finished break out of loop
             if ((boardState[row-1][column-1]).boardFinished==false) {
                choiceValid=true;
             }
             else {
                std::cout << "Please choose another board, this board has been won or drawn so is locked\n";
             }
        }
    }

    // allows player to make a move on a regular board as long as it is valid on that board
    // and is the regular board that the previous player forced this move to be on
    //make move and check winner of board
    rowColumn=(boardState[row-1][column-1]).makeMove(player);
    (boardState[row-1][column-1]).checkWinner();
    (boardState[row-1][column-1]).isBoardFinished();

    //Only need to check if bigBoard is won when regular board is won
    if ((boardState[row-1][column-1]).winner!=" ") {
        checkWinner();
    }
    //Only need to check if bigBoard is finished when regular board is done
    if ((boardState[row-1][column-1]).boardFinished==true) {
        isBoardFinished();
    }
    // make the next row  and column these values to force next player to make move in the correct board
    row=rowColumn[0];
    column=rowColumn[1];
}

//prints the big board structure
void bigBoard::printBigBoard() {
    //loop through reach row and column of big board
    for (int i=0;i<=2;i++) {
        for (int j=0;j<=2;j++) {
            //for each row of regular boards in each row of big board
            std::cout << (boardState[i][0]).getElement(j,0) << "|" << (boardState[i][0]).getElement(j,1) << "|" << (boardState[i][0]).getElement(j,2) <<  ":";
            std::cout << (boardState[i][1]).getElement(j,0) << "|" << (boardState[i][1]).getElement(j,1) << "|" << (boardState[i][1]).getElement(j,2) << ":";
            std::cout << (boardState[i][2]).getElement(j,0) << "|" << (boardState[i][2]).getElement(j,1) << "|" << (boardState[i][2]).getElement(j,2) << std::endl;
            //unless we are on the last line separate the rows
            //different regular boards separated differently
            if (j==2 && i!=2) {
                std::cout << "=================\n";
            }
            else if (j!=2) {
                std::cout << "-----------------\n";
            }
        }
    }
}

// checks if anyone has won the game through checking what combination of regular boards has been won
void bigBoard::checkWinner() {
    //check columns
    for (int i=0;i<=2;i++) {
        if (boardState[0][i].winner==boardState[1][i].winner && boardState[0][i].winner==boardState[2][i].winner && !(boardState[0][i].winner==" ")) {
        winner=boardState[0][i].winner;
        }
    }
    //check rows
    for (int i=0;i<=2;i++) {
        if (boardState[i][0].winner==boardState[i][1].winner && boardState[i][0].winner==boardState[i][2].winner && !(boardState[i][0].winner==" ")) {
        winner=boardState[i][0].winner;
        }
    }

    //diagonals
    if (boardState[0][0].winner==boardState[1][1].winner && boardState[0][0].winner==boardState[2][2].winner && !(boardState[0][0].winner==" ")) {
        winner=boardState[0][0].winner;
    }

    else if (boardState[0][2].winner==boardState[1][1].winner && boardState[0][2].winner==boardState[2][0].winner && !(boardState[0][2].winner==" ")) {
        winner=boardState[0][2].winner;       
    }
}

// if game finished, then update boardFinished for big board so we cannot make a move on the big board
// either someone has won big board or all boards are finished with no winner for big board
void bigBoard::isBoardFinished() {
    //if someone wins, game should end 
    if (winner!=" ") {
        boardFinished=true;
        return;
    }

    //now for if all regular boards are finished with no winner for big board, game is finished
    //initially bigboard set to be finished so if we find all regular boards are finished, the big boards will be finished
    boardFinished=true;
    for (int i=0;i<=2;i++) {
        for (int j=0;j<=2;j++){
            //if there is a board that isn't finished, then clearly bigboard isn't finished
            if ((boardState[i][j]).boardFinished!=true){
                boardFinished=false;
            }
        }
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

    //while no one has won and we can still make a move, play the game
    while (board1.boardFinished==false) {
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
            std::cout << "Please select an option: \n1. Make a move \n2. View the whole board \n3. View rules \n4. Quit Program\n"; 
            while (!(std::cin>>option)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Please type 1,2,3 or 4\n";
            }
            //only 1,2,3,4,5 allowed as inputs
            if (option==1) {
                board1.makeMove(currentPlayer, nextRow, nextcolumn);
                moveFinished=true;
            }
            else if (option==2) {
                board1.printBigBoard();
            }
            else if (option==3) {
                std::cout << "====================================\n";
                std::cout << "The rules are relatively simple.\n"; 
                std::cout << "Imagine a tic-tac-toe board full of tic-tac-boards.\n";
                std::cout << "The goal of the game is to win the big game of tic-tac-toe.\n";
                std::cout << "The way to do this is to win the small games of tic-tac-toe contained on the big board of tic-tac-toe.\n";
                std::cout << "You win the small games of tic-tac-toe on the big board in the normal way.\n";
                std::cout << "However, where you make a move on your regular games of tic-tac-toe determines the next board you play on\n";
                std::cout << "For example, if I make a move in the top right of a board, then the next move is played on the top right board on the big game of tic-tac-toe.\n";
                std::cout << "If the board you would have been forced to play in by the previous move has been won or drawn, then you get a free choice of board to play on.\n";
                std::cout << "The game is won when one player wins the regular tic-tac-toe boards on the big board which gives a combination that would win in tic-tac-toe.\n";
                std::cout << "For example, if noughts wins the top 3 boards on the big board.\n";
                std::cout << "Those are the basics, now you should be able to play the game.\n";
                std::cout << "====================================\n";
            }
            else if (option==4) {
                moveFinished=true;
                board1.boardFinished=true;
            }
            else {
                std::cout << "That is not a valid option \n";
            }
        }
    }
    
    //once game has been won, congratulate player or state draw has been achieved.
    board1.printBigBoard();
    if (board1.winner!=" ") {
        std::cout << "Congratulations to " << board1.winner << "\n";
    }
    else {
        std::cout << "Draw\n";
    }
    return 0;
}

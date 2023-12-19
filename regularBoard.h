#include <iostream>
#include <vector>
#include <limits>

// This is our board class - this is our regular tictactoe board
// variables are the state of the board and the winner and the number of moves and boolean boardFinished
// class methods are makeMove - making a move, printBoard - output board to screen, and checkWinner - check to see if anyone has won
// and isBoardFinished - check to see if a draw has occurred
class board {
private: 
    std::vector<std::vector<std::string>> boardState = {{" "," "," "},{" "," "," "},{" "," "," "}};
public:
    std::string winner = " "; 
    bool boardFinished=false;
    int moves=0;
    std::vector<int> makeMove(std::string player);
    void printBoard();
    void checkWinner();
    void isBoardFinished();
    std::string getElement(int row, int col);
};

// this function allows the player to make a move as long as it is valid
// takes what player is making the move so we can make sure the correct player's counter is added to the board
// returns the row and column of the
std::vector<int> board::makeMove(std::string player) {
    int row;
    int column;
    std::vector<int> rowColumn;

    //take input for row and column until it is valid and space isn't occupied
    bool validMove=false;
    while (validMove==false) {

        // take input for row until it is valid
        bool validRow = false;
        while (validRow==false) {
            std::cout << "Please select the row of the space you want to occupy (type 1,2 or 3)\n";
            // if non-int input given take input until int is inputted
            while (!(std::cin>>row)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Please type 1,2 or 3\n";
            }
            //only 1,2,3 allowed as inputs
            if (row==1 || row==2 || row==3) {
                validRow=true;
            } 
            else {
                std::cout << "That is not a valid row number \n";
            }
        }
        
        // take input for column until it is valid
        bool validColumn = false;
        while (validColumn==false) {
            std::cout << "Please select the column of the space you want to occupy (type 1,2 or 3)\n";
            // if non-int input given take input until int is inputted
            while (!(std::cin>>column)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Please type 1,2 or 3\n";
            }
            //only 1,2,3 allowed as inputs
            if (column==1 || column==2 || column==3) {
                validColumn=true;
            } 
            else {
                std::cout << "That is not a valid column number \n";
            }
        } 

        //if the space is blank we are free to make the move for whatever player is playing, increase number of moves by one
        // then change validMove to true to break out of loop
        // return row column for out valid move
        if (boardState[row-1][column-1]==" ") {
            if (player=="o") {
                boardState[row-1][column-1] = "o";
                moves++;
            } 
            else if(player=="x") {
                boardState[row-1][column-1] = "x";
                moves++;
            }
            validMove=true;
            rowColumn= {row,column};
        }    

        // already a nought/cross in this space - take another input from user
        else {
                std::cout << "Please make a valid move, this space is already taken.\n";
        }   
    }
    return rowColumn;
}  

// this function prints the current state of the board to the screen
void board::printBoard() {
        for (int i=0;i<=2;i++) {
            //print rows
            std::cout << boardState[i][0] << "|" << boardState[i][1] << "|"<< boardState[i][2] << "\n";
            //if not last row, print separation between rows
            if (i!=2) {
                std::cout << "-----\n";
            }
        }
}

//checks if someone has won and if so changes the winner variable
void board::checkWinner() {
    //check columns
    for (int i=0;i<=2;i++) {
        if (boardState[0][i]==boardState[1][i] && boardState[0][i]==boardState[2][i] && !(boardState[0][i]==" ")) {
        winner=boardState[0][i];
        }
    }
    //check rows
    for (int i=0;i<=2;i++) {
        if (boardState[i][0]==boardState[i][1] && boardState[i][0]==boardState[i][2] && !(boardState[i][0]==" ")) {
        winner=boardState[i][0];
        }
    }

    //diagonals
    if (boardState[0][0]==boardState[1][1] && boardState[0][0]==boardState[2][2] && !(boardState[0][0]==" ")) {
        winner=boardState[0][0];
    }
    else if (boardState[0][2]==boardState[1][1] && boardState[0][2]==boardState[2][0] && !(boardState[0][2]==" ")) {
        winner=boardState[0][2];
    }
}

// allows us to see if the board is finished - this function is purely for the big board
void board::isBoardFinished() {
    if (moves>=9 || winner!= " ") {
        boardFinished=true;
    }
}


std::string board::getElement(int row, int col) {
    return boardState[row][col];
}

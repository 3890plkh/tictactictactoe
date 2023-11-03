#include <iostream>
#include <vector>
#include <limits>


// This is our board class - this is our regular tictactoe board
// variables are the state of the board and the winner and the number of moves
// class methods are makeMove - making a move, printBoard - output board to screen, and checkWinner - check to see if anyone has won
class board {
private:
    std::vector<std::vector<std::string>> boardState = {{" "," "," "},{" "," "," "},{" "," "," "}};
public:
    std::string winner = " "; 
    int moves=0;
    std::vector<int> makeMove(std::string player);
    void printBoard();
    void checkWinner();
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

        //if the space is blank we are free to make the move for whatever player is playing
        // then change validMove to true to break out of loop
        // return row column for out valid move
        if (boardState[row-1][column-1]==" ") {
            if (player=="o") {
                boardState[row-1][column-1] = "o";
            } 
            else if(player=="x") {
                boardState[row-1][column-1] = "x";
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
    if (winner==" ") {
        std::cout << boardState[0][0] << "|" << boardState[0][1] << "|"<< boardState[0][2] << "\n";
        std::cout << "-----\n";
        std::cout << boardState[1][0] << "|" << boardState[1][1] << "|"<< boardState[1][2] << "\n";
        std::cout << "-----\n";
        std::cout << boardState[2][0] << "|" << boardState[2][1] << "|"<< boardState[2][2] << "\n";
    }
    else if (winner=="o") {
        std::cout << " --- \n";
        std::cout << "|   |\n";
        std::cout << "|   |\n";
        std::cout << "|   |\n";
        std::cout << " --- \n";
    }
    else if (winner=="x") {
        std::cout << "\\   /\n";
        std::cout << " \\ / \n";
        std::cout << "  X  \n";
        std::cout << " / \\ \n";
        std::cout << "/   \\" << "\n";
    }
}

//checks if someone has won and if so changes the winner variable
void board::checkWinner() {
    if (boardState[0][0]==boardState[1][0] && boardState[0][0]==boardState[2][0] && !(boardState[0][0]==" ")) {
        winner=boardState[0][0];
    }
    else if (boardState[0][0]==boardState[1][1] && boardState[0][0]==boardState[2][2] && !(boardState[0][0]==" ")) {
        winner=boardState[0][0];
    }
    else if (boardState[0][0]==boardState[0][1] && boardState[0][0]==boardState[0][2] && !(boardState[0][0]==" ")) {
        winner=boardState[0][0];
    }
    else if (boardState[0][1]==boardState[1][1] && boardState[0][1]==boardState[2][1] && !(boardState[0][1]==" ")) {
        winner=boardState[0][1];
    }
    else if (boardState[0][2]==boardState[1][1] && boardState[0][2]==boardState[2][0] && !(boardState[0][2]==" ")) {
        winner=boardState[0][2];
    }
    else if (boardState[0][2]==boardState[1][2] && boardState[0][2]==boardState[2][2] && !(boardState[0][2]==" ")) {
        winner=boardState[0][2];
    }
    else if (boardState[1][0]==boardState[1][1] && boardState[1][0]==boardState[1][2] && !(boardState[1][0]==" ")) {
        winner=boardState[1][0]; 
    }
    else if (boardState[2][0]==boardState[2][1] && boardState[2][0]==boardState[2][2] && !(boardState[2][0]==" ")) {
        winner=boardState[2][0];
    }
}

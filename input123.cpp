#include <iostream>
#include <limits>

//take an input until the inputs are ints 1,2 or 3
void input123(int& val1, int& val2) {
    bool validMove=false;
    while (validMove==false) {

    // take input for val1 until it is valid
        bool validRow = false;
        while (validRow==false) {
            std::cout << "Please select the row of the board (type 1,2 or 3)\n";
            
            // if non-int input given take input until int is inputted
            while (!(std::cin>>val1)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Please type 1,2 or 3\n";
            }
            
            //only 1,2,3 allowed as inputs
            if (val1==1 || val1==2 || val1==3) {
                validRow=true;
            } 
            else {
                std::cout << "That is not a valid row number \n";
            }
        }
        
        // take input for column until it is valid
        bool validColumn = false;
        while (validColumn==false) {
            std::cout << "Please select the column of the board(type 1,2 or 3)\n";
            // if non-int input given take input until int is inputted
            while (!(std::cin>>val2)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Please type 1,2 or 3\n";
            }
            
            //only 1,2,3 allowed as inputs
            if (val2==1 || val2==2 || val2==3) {
                validColumn=true;
            } 
            else {
                std::cout << "That is not a valid column number \n";
            }
        }
        validMove=true;
    }
}

#include <iostream>
#include <fstream>
#include <string>

const int BoardSize = 10;

class Board {
private:
    char grid[BoardSize][BoardSize];
public:
    Board(){};
    void setCell(int line, int row, char value);
    //char getCell(int line, int row);

    void print();
    //bool applyAttack(int line, int row);
};

void Board::setCell(int line, int row, char value){
    grid[line][row] = value;
}

void Board::print(){
    for(int i = 0; i < BoardSize; i++){
        for(int j = 0; j < BoardSize; j++){
            std::cout << grid[i][j];
        }
        std::cout << std::endl;
    }
}

void printHelp(){
    std::cout << "---Battleship---" << std::endl;
    std::cout << "help - prints manual" << std::endl;
    std::cout << "new_game - makes fresh new game" << std::endl;
    std::cout << "place <ship_coords> - places ships. Each ships coordinates must be explicitely given" << std::endl;
    std::cout << "status - prints stats of ongoing game" << std::endl;
    std::cout << "reveal - prints player and computer game boards" << std::endl;
}

int convertOptionToInt(std::string arg){
    if(arg == "help") return 1;
    else if(arg == "new_game") return 2;
    else if(arg == "place") return 3;
    else if(arg == "status") return 4;
    else if(arg == "reveal") return 5;
    else return -1;
}

void newGame(){
    //open setup_info file 
    std::ifstream setup_info("setup_info.txt");

    //set game_ongoing to false
    

}


int main(int argc, char* argv[])
{
    std::string option;
    if(argc <= 1){
        std::cout << "Error: Not enough arguments!" << std::endl;
    }
    else{
        std::string option = argv[1];
        int intOption = convertOptionToInt(option);
        switch(intOption){
            //help
            case 1:
                printHelp();
                break;
            //new_game
            case 2:

            //place
            case 3:
            //status
            case 4:
            //reveal
            case 5:

            default:
                std::cout << "Error: Unknown Command!" << std::endl;
                return -1; 
        }
    }

    /*
    //open file 
    std::ifstream player_file("player_board.txt");


    //read file and create Board object
    Board playerBoard;

    for(int i = 0; i < BoardSize; i++){
        std::string line;
        getline(player_file, line);
        for(int j = 0; j < BoardSize; j++){
            playerBoard.setCell(i, j, line[j]);
        }
    }

    
    //print Board
    playerBoard.print();

    //close file
    player_file.close();
    */
    
}
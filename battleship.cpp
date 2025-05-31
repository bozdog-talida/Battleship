#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

const int BoardSize = 10;

//Converting letters (from the text file with coordinates) to rows
int LetterToRow(char letter){
    letter = toupper(letter);
    return int(letter) - 65;
}

//Converting a string to a row and a column
void ParseCoordinates(string coord, int& row, int& column){
    row = LetterToRow(coord[0]);
    column = coord[1] - '0';
}

// Reading attack coordinates and storing them in a vector for later use
void ReadAttacks(string filename, vector <string>& attacks){
    ifstream MyFile(filename);
    string coord;
    while(MyFile >> coord){
        attacks.push_back(coord);
    }
}

//Ship class in order to implement composition
class Ship {
private:
    vector<string> coordinates;
public:
    Ship() {}
    void addCoordinate(string coord) {
        coordinates.push_back(coord);
    }
    /*Returns a read-only reference to the coordinates vector.
    The first 'const' means the vector can't be modified.
    The second 'const' means this method doesn't change the Ship object.*/
    const vector<string>& getCoordinates() const {
        return coordinates;
    }
};

class Board {
private:
    char grid[BoardSize][BoardSize];
public:
    Board(){};
    char& at(int row, int column);
    void print();
    bool applyAttack(string coord);
    int countShips();
    vector<Ship> ships;
};

//Accessing cells on the board
char& Board::at(int row, int column){
    return grid[row][column];
}

//Printing the board
void Board::print(){
    cout << "  ";
    for (int column = 0; column < BoardSize; column++) {
        cout << column << " ";
    }
    cout << endl;

    for (int row = 0; row < BoardSize; row++) {
        cout << char('A' + row) << " ";
        for (int column = 0; column < BoardSize; column++) {
            cout << grid[row][column] << " ";
        }
        cout << endl;
    }
}

//Attacking the other board and marking whether it was a hit or a miss
bool Board::applyAttack(string coord){
    int row, column;
    ParseCoordinates(coord, row, column);
    if (at(row, column) == 'S'){
        at(row, column) = 'X';
        cout << "Hit!" << endl;
        return true;
    }
    else if (at(row, column) == '.'){
        at(row, column) = 'O';
        cout << "Miss!" << endl;
        return false;
    }
    else {
        cout << "Already attacked.";
        return false;
    }
}

//Counting the remaining ships on the board
int Board::countShips(){
    int shipsLeft = 0;
    for (int i = 0; i < BoardSize; i++){
        for (int j = 0; j < BoardSize; j++){
            if (at(i, j) == 'S'){
                shipsLeft++;
            }
        }
    }
    return shipsLeft;
}

//Generating a random attack coordinate
string generateRandomCoordinate() {
    char row = 'A' + rand() % 10;
    char column = rand() % 10;
    string coordinate = "";
    coordinate += row;
    coordinate += to_string(column);
    return coordinate;
}

int main(){
    Board Board1;
    Board Board2;

    /*Ship placement is assumed to have been done by App1.
      App1 must fill Board1 with ships for the human player
      and Board2 with ships for the computer.
      This must be done before the game is run.*/

    vector <string> attacksPlayer1;
    vector <string> alreadyAttackedByComputer;

    // This file must be created by App1 and should contain Player 1's attack sequence.
    // Player2 is the computer, so it does NOT require another file.
    ReadAttacks("AttackedPlayer1.txt", attacksPlayer1);

    //Simulating the turns between the player and the computer
    size_t i = 0;
    srand(time(0)); // Current time is used as seed for the random generator
    while (i < attacksPlayer1.size()){
        if (i < attacksPlayer1.size()){
            cout << "Player 1 attacks " << attacksPlayer1[i] << endl;
            Board2.applyAttack(attacksPlayer1[i]);
            if (Board2.countShips() == 0){
                cout << "Player 1 wins!" << endl;
                break;
            }
            i++;
        }

        /* Computer generates its move live during the game.
           Keeps generating a new coordinate until one that has not been used before is found.*/
        string computerCoordinate;
        bool alreadyUsedCoordinate;
        do {
            computerCoordinate = generateRandomCoordinate();
            alreadyUsedCoordinate = false;
            for (int k = 0; k < alreadyAttackedByComputer.size(); k++){
                if (alreadyAttackedByComputer[k] == computerCoordinate){
                    alreadyUsedCoordinate = true;
                    break;
                }
            }
        } while(alreadyUsedCoordinate);

        alreadyAttackedByComputer.push_back(computerCoordinate);
        cout << "Computer attacks: " << computerCoordinate << endl;
        Board1.applyAttack(computerCoordinate);

        if (Board1.countShips() == 0){
            cout << "Computer wins!" << endl;
            break;
        }
    }
    Board1.print();
    Board2.print();
    return 0;
}

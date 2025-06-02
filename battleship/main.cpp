#include "Board.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

// Generates a random valid coordinate in format like "C7"
string generateRandomCoordinate() {
    char row = 'A' + rand() % 10;
    char column = '0' + rand() % 10;
    return string(1, row) + column;
}

int main(int argc, char* argv[]) {
    // Expect exactly 3 arguments: attack coordinate, board1 file, board2 file
    if (argc != 4) {
        cout << "Usage: " << argv[0] << " <player1_attack_coord> <board1_file> <board2_file>\n";
        return 1;
    }

    string attackCoord = argv[1]; // Coordinate of player 1's attack (e.g. A3)
    string board1File = argv[2]; // File for Player 1's board
    string board2File = argv[3]; // File for Computer's board

    Board Board1;
    Board Board2;

    // Load both boards from file at the start of each run
    Board1.loadFromFile(board1File);
    Board2.loadFromFile(board2File);

    // Prevent the game from continuing after someone already won
    if (Board1.countShips() == 0 || Board2.countShips() == 0) {
        if (Board1.countShips() == 0)
            cout << "Game over: Computer already won." << endl;
        else
            cout << "Game over: Player 1 already won." << endl;
        return 0;
    }

    srand(time(0)); // Seed random number generator for computer attack

    // Player 1 attacks Computer's board
    cout << "Player 1 attacks " << attackCoord << endl;
    Board2.applyAttack(attackCoord);

    // Check if Computer has lost all ships after the attack
    if (Board2.countShips() == 0) {
        cout << "Player 1 wins!" << endl;
        Board1.saveToFile(board1File);
        Board2.saveToFile(board2File);
        return 0;
    }

    // Computer randomly chooses a coordinate that hasn't been attacked
    string computerCoordinate;
    bool valid = false;
    do {
        computerCoordinate = generateRandomCoordinate();
        int row, col;
        ParseCoordinates(computerCoordinate, row, col);
        char cell = Board1.at(row, col);
        if (cell == 'S' || cell == '.') valid = true;
    } while (!valid);

    // Computer performs attack on Player 1's board
    cout << "Computer attacks: " << computerCoordinate << endl;
    Board1.applyAttack(computerCoordinate);

    // Check if Player 1 has lost all ships after the attack
    if (Board1.countShips() == 0) {
        cout << "Computer wins!" << endl;
    }

    // Save updated boards after each round
    Board1.saveToFile(board1File);
    Board2.saveToFile(board2File);

    return 0;
}

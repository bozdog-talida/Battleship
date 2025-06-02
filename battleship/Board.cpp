#include "Board.h"
#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

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

// Reads the board state from a text file into a 2D grid
void ReadBoardFromFile(string filename, char board[BoardSize][BoardSize]){
    ifstream file(filename);
    for (int i = 0; i < BoardSize; ++i)
        for (int j = 0; j < BoardSize; ++j)
            file >> board[i][j];
}

// Writes the current board state to a text file
void WriteBoardToFile(string filename, char board[BoardSize][BoardSize]){
    ofstream file(filename);
    for (int i = 0; i < BoardSize; ++i) {
        for (int j = 0; j < BoardSize; ++j) {
            file << board[i][j] << " ";
        }
        file << "\n";
    }
}

Board::Board() {}

// Loads the board from a file
void Board::loadFromFile(string filename) {
    ReadBoardFromFile(filename, grid);
}

// Saves the board to a file
void Board::saveToFile(string filename) {
    WriteBoardToFile(filename, grid);
}

char& Board::at(int row, int column) {
    return grid[row][column];
}

// Prints the current state of the board
void Board::print() {
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

// Applies an attack to the board at the given coordinate
// Marks hits with 'X', misses with 'O', already attacked spots stay unchanged
bool Board::applyAttack(string coord) {
    int row, column;
    ParseCoordinates(coord, row, column);
    if (at(row, column) == 'S') {
        at(row, column) = 'X';
        cout << "Hit!" << endl;
        return true;
    } else if (at(row, column) == '.') {
        at(row, column) = 'O';
        cout << "Miss!" << endl;
        return false;
    } else {
        cout << "Already attacked." << endl;
        return false;
    }
}

// Counts how many ship cells ('S') are still on the board
int Board::countShips() {
    int shipsLeft = 0;
    for (int i = 0; i < BoardSize; i++)
        for (int j = 0; j < BoardSize; j++)
            if (at(i, j) == 'S')
                shipsLeft++;
    return shipsLeft;
}


#ifndef ASSIGNMENT_DEMO_PYRAMID_X_O_H
#define ASSIGNMENT_DEMO_PYRAMID_X_O_H

#include "BoardGame_Classes.h"

template<typename T>
class PyramidBoard : public Board<T> {
public:
    PyramidBoard();
    bool updateBoard(int row, int col, T value);
    void display();
    bool checkWin();
    bool checkDraw();
    bool isGameOver();
    ~PyramidBoard() {
        for (int i = 0; i < this->rows; i++) {
            delete[] this->grid[i];
        }
        delete[] this->grid;
    }
};

template<typename T>
class PyramidPlayer : public Player<T> {
public:
    PyramidPlayer() {}
    PyramidPlayer(std::string playerName, T symbol);
    void getMove(int& row, int& col);
};

template<typename T>
class RandomPyramidPlayer : public RandomPlayer<T> {
public:
    int colCount;
    void getMove(int& row, int& col) override;
    RandomPyramidPlayer(T symbol);
};

#include <bits/stdc++.h>

template<typename T>
PyramidBoard<T>::PyramidBoard() {
    this->cols = 5;
    this->rows = 3;
    this->grid = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->grid[i] = new char[this->cols];
        for (int j = 0; j < this->cols; j++) {
            if ((i == 0 && j != 2) || (i == 1 && j == 0) || (i == 1 && j == 4)) {
                this->grid[i][j] = 'X';
            } else {
                this->grid[i][j] = '-';
            }
        }
    }
    this->moveCount = 0;
}

template<typename T>
bool PyramidBoard<T>::updateBoard(int row, int col, T value) {
    if (row < 0 || row >= this->rows || col < 0 || col >= this->cols) {
        return false;
    }
    if (this->grid[row][col] == '-' || value == '-') {
        if (value == '-') {
            if (this->grid[row][col] != 'X') {
                this->moveCount--;
                this->grid[row][col] = '-';
            }
        } else {
            this->moveCount++;
            this->grid[row][col] = toupper(value);
        }
        return true;
    }
    return false;
}

template<typename T>
void PyramidBoard<T>::display() {
    for (int i = 0; i < this->rows; i++) {
        std::cout << "\n ";
        for (int j = 0; j < this->cols; j++) {
            if (i == 0 && j + 1 == this->cols) std::cout << "\n              ------------------------------------------";
            else if (i == 1 && j + 1 == this->cols) std::cout << "\n        -----------------------------------------------------------";

            if (this->grid[i][j] != 'X') {
                if (i == 0) {
                    std::cout << "                              |(" << i << "," << j << ")  ";
                    std::cout << std::setw(2) << this->grid[i][j] << "|";
                } else if (i == 1) {
                    std::cout << "         |(" << i << "," << j << ")  ";
                    std::cout << std::setw(2) << this->grid[i][j] << " |";
                } else if (i == 2) {
                    std::cout << "|(" << i << "," << j << ")    ";
                    std::cout << std::setw(2) << this->grid[i][j] << " |";
                    if (j == 4) {
                        std::cout << "|(" << i << "," << j << ")    ";
                        std::cout << std::setw(2) << this->grid[i][j] << " |";
                        std::cout << "\n----------------------------------------------------------------------------------";
                    }
                }
            }
        }
    }
    std::cout << std::endl;
}

template<typename T>
bool PyramidBoard<T>::checkWin() {
    for (int col = 0; col < this->cols; col++) {
        if (this->grid[0][col] != '-' && this->grid[0][col] != 'X' &&
            this->grid[0][col] == this->grid[1][col] &&
            this->grid[1][col] == this->grid[2][col]) {
            return true;
        }
    }
    for (int row = 0; row < this->rows; row++) {
        T firstSymbol = '-';
        bool isWinningRow = true;
        for (int col = 0; col < this->cols; col++) {
            if (this->grid[row][col] == 'X' || this->grid[row][col] == '-') {
                isWinningRow = false;
                break;
            }
            if (firstSymbol == '-') {
                firstSymbol = this->grid[row][col];
            } else if (this->grid[row][col] != firstSymbol) {
                isWinningRow = false;
                break;
            }
        }
        if (isWinningRow && firstSymbol != '-') {
            return true;
        }
    }
    if (this->grid[0][2] != '-' && this->grid[0][2] != 'X') {
        if (this->grid[0][2] == this->grid[1][3] && this->grid[1][3] == this->grid[2][4]) {
            return true;
        }
        if (this->grid[0][2] == this->grid[1][1] && this->grid[1][1] == this->grid[2][0]) {
            return true;
        }
    }
    return false;
}

template<typename T>
bool PyramidBoard<T>::checkDraw() {
    return (this->moveCount == 9 && !checkWin());
}

template<typename T>
bool PyramidBoard<T>::isGameOver() {
    return checkWin() || checkDraw();
}

template<typename T>
PyramidPlayer<T>::PyramidPlayer(std::string playerName, T symbol) : Player<T>(playerName, symbol) {}

template<typename T>
void PyramidPlayer<T>::getMove(int& row, int& col) {
    std::cout << "\nPlease enter your move row (0 to 2) and col (0 to 4) separated by spaces: ";
    std::cin >> row >> col;
}

template<typename T>
RandomPyramidPlayer<T>::RandomPyramidPlayer(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->colCount = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template<typename T>
void RandomPyramidPlayer<T>::getMove(int& row, int& col) {
    row = rand() % this->dimension;
    col = rand() % this->colCount;
}

#endif
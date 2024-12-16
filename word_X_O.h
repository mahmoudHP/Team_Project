#ifndef GAME_WORDS_X_O_H
#define GAME_WORDS_X_O_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <set>
#include <cstdlib>
#include <ctime>

template<typename T>
class WordGameBoard {
public:
    std::set<std::string> dictionary;

    WordGameBoard();
    bool updateBoard(int x, int y, T symbol);
    void displayBoard();
    bool checkWin();
    bool checkDraw();
    bool isGameOver();
    ~WordGameBoard() {
        for (int i = 0; i < rows; i++) {
            delete[] board[i];
        }
        delete[] board;
    }

private:
    int rows;
    int columns;
    T** board;
    int movesCount;
};

template<typename T>
class WordGamePlayer {
public:
    WordGamePlayer() {}
    WordGamePlayer(std::string playerName, T symbol);
    void getMove(int& x, int& y);

private:
    std::string name;
    T symbol;
};

template <typename T>
class RandomWordGamePlayer {
public:
    void getMove(int& x, int& y);
    RandomWordGamePlayer(T symbol);

private:
    int dimension;
    T symbol;
    std::string name;
};

// ____________________________________________________________________________________________

template<typename T>
WordGameBoard<T>::WordGameBoard() {
    columns = 3;
    rows = 3;
    board = new T*[rows];
    for (int i = 0; i < rows; i++) {
        board[i] = new T[columns];
        for (int j = 0; j < columns; j++) {
            board[i][j] = '-';
        }
    }

    std::ifstream file("dic.txt");
    if (file.is_open()) {
        std::string word;
        while (file >> word) {
            dictionary.insert(word);
        }
        file.close();
    }

    movesCount = 0;
}

template<typename T>
bool WordGameBoard<T>::updateBoard(int x, int y, T symbol) {
    if (x < 0 || x >= rows || y < 0 || y >= columns || board[x][y] != '-') {
        return false;
    }
    movesCount++;
    board[x][y] = toupper(symbol);
    return true;
}

template<typename T>
void WordGameBoard<T>::displayBoard() {
    for (int i = 0; i < rows; i++) {
        std::cout << "\n| ";
        for (int j = 0; j < columns; j++) {
            std::cout << "(" << i << "," << j << ") " << std::setw(2) << board[i][j] << " |";
        }
        std::cout << "\n----------------------------------------";
    }
    std::cout << std::endl;
}

template<typename T>
bool WordGameBoard<T>::checkWin() {
    std::string check;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <= columns - 3; j++) {
            check = {board[i][j], board[i][j + 1], board[i][j + 2]};
            if (dictionary.find(check) != dictionary.end()) {
                return true;
            }
        }
    }

    for (int i = 0; i <= rows - 3; i++) {
        for (int j = 0; j < columns; j++) {
            check = {board[i][j], board[i + 1][j], board[i + 2][j]};
            if (dictionary.find(check) != dictionary.end()) {
                return true;
            }
        }
    }

    for (int i = 0; i <= rows - 3; i++) {
        for (int j = 0; j <= columns - 3; j++) {
            check = {board[i][j], board[i + 1][j + 1], board[i + 2][j + 2]};
            if (dictionary.find(check) != dictionary.end()) {
                return true;
            }
        }
    }
    for (int i = 0; i <= rows - 3; i++) {
        for (int j = 2; j < columns; j++) {
            check = {board[i][j], board[i + 1][j - 1], board[i + 2][j - 2]};
            if (dictionary.find(check) != dictionary.end()) {
                return true;
            }
        }
    }

    return false;
}

template<typename T>
bool WordGameBoard<T>::checkDraw() {
    return (movesCount == 9 && !checkWin());
}

template<typename T>
bool WordGameBoard<T>::isGameOver() {
    return checkWin() || checkDraw();
}

//_______________________________________________________________________________________
template<typename T>
WordGamePlayer<T>::WordGamePlayer(std::string playerName, T s) : name(playerName), symbol(s) {}

template <typename T>
void WordGamePlayer<T>::getMove(int& x, int& y) {
    std::cout << "\nPlease enter your move x(0 to 2) and y(0 to 2) separated by spaces: ";
    std::cin >> x >> y;
    std::cout << "Enter a char to play (A to Z): ";
    std::cin >> symbol;
}

template <typename T>
RandomWordGamePlayer<T>::RandomWordGamePlayer(T symbol) : symbol(symbol) {
    dimension = 3;
    name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void RandomWordGamePlayer<T>::getMove(int& x, int& y) {
    x = rand() % dimension;
    y = rand() % dimension;

    int randomIndex = rand() % 26;
    char randomSymbol = 'A' + randomIndex;
    symbol = randomSymbol;
}

#endif // GAME_WORDS_X_O_H
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// Function prototypes for the games
void ultimate_tic_tac_toe();
void xo_game_manager();

// Game 1: Ultimate Tic Tac Toe Functions
int play_small_board(char small_board[3][3], char player);
bool check_small_win(char small_board[3][3], char player);
bool is_draw_small(char small_board[3][3]);
bool check_meta_win(char meta_board[3][3], char player);

// Game 2: X-O Game Management
template <typename T>
class Board {
protected:
    int rows, columns;
    T** board;
    int n_moves = 0;

public:
    virtual bool update_board(int x, int y, T symbol) = 0;
    virtual void display_board() = 0;
    virtual bool is_win() = 0;
    virtual bool is_draw() = 0;
    virtual bool game_is_over() = 0;
    virtual ~Board() {}
};

template <typename T>
class X_O_Board : public Board<T> {
public:
    X_O_Board() {
        this->rows = this->columns = 3;
        this->board = new T*[this->rows];
        for (int i = 0; i < this->rows; ++i) {
            this->board[i] = new T[this->columns]();
        }
    }

    ~X_O_Board() {
        for (int i = 0; i < this->rows; ++i) {
            delete[] this->board[i];
        }
        delete[] this->board;
    }

    bool update_board(int x, int y, T symbol) override {
        if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == 0) {
            this->board[x][y] = symbol;
            ++this->n_moves;
            return true;
        }
        return false;
    }

    void display_board() override {
        cout << "  0 1 2\n";
        for (int i = 0; i < this->rows; ++i) {
            cout << i << " ";
            for (int j = 0; j < this->columns; ++j) {
                cout << (this->board[i][j] ? this->board[i][j] : '.') << " ";
            }
            cout << endl;
        }
    }

    bool is_win() override {
        for (int i = 0; i < 3; ++i) {
            if (this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2]) return true;
        }

        for (int j = 0; j < 3; ++j) {
            if (this->board[0][j] == this->board[1][j] && this->board[1][j] == this->board[2][j]) return true;
        }

        if (this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2]) return true;
        if (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0]) return true;

        return false;
    }

    bool is_draw() override {
        return this->n_moves == 9 && !is_win();
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }
};

int main() {
    srand(time(0)); // Seed random number generator

    int choice;
    cout << "Welcome to the Game Hub! :)\n";
    cout << "Select the game you want to play:\n";
    cout << "1. Ultimate Tic Tac Toe\n";
    cout << "2. Classic X-O Game\n";
    cout << "Enter your choice (1/2): ";
    cin >> choice;

    switch (choice) {
        case 1:
            ultimate_tic_tac_toe();
            break;
        case 2:
            xo_game_manager();
            break;
        default:
            cout << "Invalid choice. Exiting...\n";
            break;
    }

    return 0;
}

// Ultimate Tic Tac Toe Implementation
void ultimate_tic_tac_toe() {
    char meta_board[3][3] = { '\0' };
    char small_boards[3][3][3][3] = { '\0' };
    char player = 'X';

    while (true) {
        cout << "\nMeta-Game Board Status:\n";
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout << (meta_board[i][j] == '\0' ? '.' : meta_board[i][j]) << " ";
            }
            cout << endl;
        }

        int sb_row, sb_col;
        cout << "\n" << player << "'s turn. Select a small board to play (row col): ";
        cin >> sb_row >> sb_col;

        if (sb_row >= 0 && sb_row < 3 && sb_col >= 0 && sb_col < 3 && meta_board[sb_row][sb_col] == '\0') {
            meta_board[sb_row][sb_col] = player;
            if (player == 'X') player = 'O';
            else player = 'X';
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }
}

// X-O Game manager
void xo_game_manager() {
    cout << "Game manager placeholder invoked.\n";
}

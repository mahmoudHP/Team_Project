#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Function to display a single Tic Tac Toe small board
void display_small_board(char small_board[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << (small_board[i][j] == '\0' ? '.' : small_board[i][j]) << " ";
        }
        cout << endl;
    }
}

// Function to check if a player has won on a small board
bool check_small_win(char small_board[3][3], char player) {
    // Check rows, columns, and diagonals
    for (int i = 0; i < 3; ++i) {
        if (small_board[i][0] == player && small_board[i][1] == player && small_board[i][2] == player) return true;
        if (small_board[0][i] == player && small_board[1][i] == player && small_board[2][i] == player) return true;
    }
    if (small_board[0][0] == player && small_board[1][1] == player && small_board[2][2] == player) return true;
    if (small_board[0][2] == player && small_board[1][1] == player && small_board[2][0] == player) return true;
    return false;
}

// Function to check if a small board is a draw
bool is_draw_small(char small_board[3][3]) {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (small_board[i][j] == '\0') return false;
    return true;
}

// Function to handle a single small game within a small Tic Tac Toe board
int play_small_board(char small_board[3][3], char player) {
    int x, y;
    while (true) {
        cout << player << "'s move: ";
        cin >> x >> y;
        if (x >= 0 && x < 3 && y >= 0 && y < 3 && small_board[x][y] == '\0') {
            small_board[x][y] = player;
            display_small_board(small_board);
            if (check_small_win(small_board, player)) {
                return 1; // Player wins this small game
            }
            if (is_draw_small(small_board)) {
                return 0; // Draw in the small game
            }
            return 0;
        } else {
            cout << "Invalid move. Try again.\n";
        }
    }
}

// Function to check if the meta-game board has a winner
bool check_meta_win(char meta_board[3][3], char player) {
    for (int i = 0; i < 3; ++i) {
        if (meta_board[i][0] == player && meta_board[i][1] == player && meta_board[i][2] == player) return true;
        if (meta_board[0][i] == player && meta_board[1][i] == player && meta_board[2][i] == player) return true;
    }
    if (meta_board[0][0] == player && meta_board[1][1] == player && meta_board[2][2] == player) return true;
    if (meta_board[0][2] == player && meta_board[1][1] == player && meta_board[2][0] == player) return true;
    return false;
}

// Main function to run Ultimate Tic Tac Toe
int main() {
    srand(time(0));

    // 3x3 meta-board of small Tic Tac Toe games
    char meta_board[3][3] = { '\0' };
    char small_boards[3][3][3][3] = { '\0' };
    char player = 'X';

    while (true) {
        // Display Meta Board Status
        cout << "\nMeta-Game Board Status:\n";
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout << (meta_board[i][j] == '\0' ? '.' : meta_board[i][j]) << " ";
            }
            cout << endl;
        }

        // Ask player to select a small board to play
        int sb_row, sb_col;
        cout << "\n" << player << "'s turn. Select a small board to play (row col): ";
        cin >> sb_row >> sb_col;

        if (sb_row >= 0 && sb_row < 3 && sb_col >= 0 && sb_col < 3 && meta_board[sb_row][sb_col] == '\0') {
            // Play the selected small game
            int result = play_small_board(small_boards[sb_row][sb_col], player);
            if (result == 1) { // If player wins the small game
                meta_board[ sb_row ][ sb_col ] = player;
                if (check_meta_win(meta_board, player)) {
                    cout << player << " wins the Ultimate Tic Tac Toe Game!\n";
                    break;
                }
            }
            player = (player == 'X') ? 'O' : 'X';
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}

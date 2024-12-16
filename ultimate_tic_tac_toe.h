#ifndef ULTIMATE_TIC_TAC_TOE_H
#define ULTIMATE_TIC_TAC_TOE_H

#include <iostream>
using namespace std;


void ultimate_tic_tac_toe() {
    char meta_board[3][3] = { '\0' };
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
            player = (player == 'X') ? 'O' : 'X';
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }
}

#endif

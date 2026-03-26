#include <iostream>
#include <string>
#include <vector>

#include "../include/Wallet.h"
#include "../include/Bank.h"
#include "../include/ticTacToe.h"

using namespace std;

void TicTacToe::initializeBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
    currentPlayer = 'X';
}

bool TicTacToe::isBoardFull() {
    for (int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

void TicTacToe::makeMove(int row, int col) {
    if (board[row][col] == ' ') {
        board[row][col] = currentPlayer;
    }
}

int TicTacToe::checkWin() {
    int winner = 0;
    // Check rows and columns
    for(int i = 0; i < 3; i++) {
        if(board[i][0] == board [i][1] && board [i][1] == board[i][2] && board[i][0] != ' ') {
            winner = (board[i][0] == currentPlayer) ? 1 : 2;
        }
        if(board[0][i] == board [1][i] && board [1][i] == board[2][i] && board[0][i] != ' ') {
            winner = (board[i][0] == currentPlayer) ? 1 : 2;
        }
        //Check diagonals
        if(board[0][0] == board [1][1] && board [1][1] == board[2][2] && board[0][0] != ' ') {
            winner = (board[i][0] == currentPlayer) ? 1 : 2;
        }
        if(board[0][2] == board[1][1] && board [1][1] == board[2][0] && board[0][2] != ' ') {
            winner = (board[i][0] == currentPlayer) ? 1 : 2;
        }
    }
    return winner;
}
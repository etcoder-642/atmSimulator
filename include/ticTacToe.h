#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <iostream>
#include <string>
#include <vector>

#include "../include/Wallet.h"
#include "../include/Bank.h"
using namespace std;

class TicTacToe {
    private:
        char board[3][3];
        char currentPlayer;
        public:
        const char (&getBoard() const)[3][3] {
            return board;
        }
        char getCurrentPlayer() {
            return currentPlayer;
        }
        char switchPlayer() {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            return currentPlayer;
        }
    public:
        void initializeBoard();
        bool isBoardFull();
        void makeMove(int row, int col);
        int checkWin();
};

#endif
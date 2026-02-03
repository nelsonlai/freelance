/**
 * Solution 8.4: Tic-Tac-Toe Game
 * Week 8 - Advanced Arrays and Strings
 * 
 * Description: Tic-tac-toe game using 2D array
 */

#include <stdio.h>

char board[3][3];

void initializeBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
        if (i < 2) {
            printf("---|---|---\n");
        }
    }
    printf("\n");
}

int checkWin() {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
            return 1;
        }
    }
    
    // Check columns
    for (int j = 0; j < 3; j++) {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j] != ' ') {
            return 1;
        }
    }
    
    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
        return 1;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') {
        return 1;
    }
    
    return 0;
}

int isBoardFull() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    int row, col;
    char currentPlayer = 'X';
    
    initializeBoard();
    
    printf("Tic-Tac-Toe Game\n");
    printf("Players take turns. Enter row (0-2) and column (0-2).\n");
    
    while (1) {
        printBoard();
        
        printf("Player %c, enter your move (row col): ", currentPlayer);
        scanf("%d %d", &row, &col);
        
        if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ') {
            printf("Invalid move! Try again.\n");
            continue;
        }
        
        board[row][col] = currentPlayer;
        
        if (checkWin()) {
            printBoard();
            printf("Player %c wins!\n", currentPlayer);
            break;
        }
        
        if (isBoardFull()) {
            printBoard();
            printf("It's a draw!\n");
            break;
        }
        
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
    
    return 0;
}
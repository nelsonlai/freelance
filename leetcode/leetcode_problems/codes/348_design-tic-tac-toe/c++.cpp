/*
 * Problem: Design Tic-Tac-Toe
 * Difficulty: Medium
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>

using namespace std;

class TicTacToe {
private:
    int n;
    vector<int> rows;
    vector<int> cols;
    int diag;
    int antiDiag;

public:
    TicTacToe(int n) {
        this->n = n;
        this->rows = vector<int>(n, 0);
        this->cols = vector<int>(n, 0);
        this->diag = 0;
        this->antiDiag = 0;
    }
    
    int move(int row, int col, int player) {
        int value = player == 1 ? 1 : -1;
        
        rows[row] += value;
        cols[col] += value;
        
        if (row == col) {
            diag += value;
        }
        if (row + col == n - 1) {
            antiDiag += value;
        }
        
        if (abs(rows[row]) == n || abs(cols[col]) == n || 
            abs(diag) == n || abs(antiDiag) == n) {
            return player;
        }
        
        return 0;
    }
};

/**
 * Your TicTacToe object will be instantiated and called as such:
 * TicTacToe* obj = new TicTacToe(n);
 * int param_1 = obj->move(row,col,player);
 */
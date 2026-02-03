#include <vector>
#include <string>

using namespace std;

class Solution {
private:
    bool win(vector<string>& board, char player) {
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
                return true;
            }
            if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
                return true;
            }
        }
        if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
            return true;
        }
        if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
            return true;
        }
        return false;
    }

public:
    bool validTicTacToe(vector<string>& board) {
        int xCount = 0, oCount = 0;
        for (string row : board) {
            for (char c : row) {
                if (c == 'X') xCount++;
                if (c == 'O') oCount++;
            }
        }
        
        bool xWin = win(board, 'X');
        bool oWin = win(board, 'O');
        
        if (xWin && oWin) {
            return false;
        }
        if (xWin) {
            return xCount == oCount + 1;
        }
        if (oWin) {
            return xCount == oCount;
        }
        return xCount == oCount || xCount == oCount + 1;
    }
};

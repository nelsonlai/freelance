/*
 * Problem: Surrounded Regions
 * Difficulty: Medium
 * Tags: array, graph, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
using namespace std;

class Solution {
private:
    void dfs(vector<vector<char>>& board, int r, int c) {
        if (r < 0 || r >= board.size() || c < 0 || c >= board[0].size() || board[r][c] != 'O') {
            return;
        }
        
        board[r][c] = '#';
        dfs(board, r + 1, c);
        dfs(board, r - 1, c);
        dfs(board, r, c + 1);
        dfs(board, r, c - 1);
    }
    
public:
    void solve(vector<vector<char>>& board) {
        if (board.empty() || board[0].empty()) {
            return;
        }
        
        int rows = board.size();
        int cols = board[0].size();
        
        for (int r = 0; r < rows; r++) {
            if (board[r][0] == 'O') {
                dfs(board, r, 0);
            }
            if (board[r][cols - 1] == 'O') {
                dfs(board, r, cols - 1);
            }
        }
        
        for (int c = 0; c < cols; c++) {
            if (board[0][c] == 'O') {
                dfs(board, 0, c);
            }
            if (board[rows - 1][c] == 'O') {
                dfs(board, rows - 1, c);
            }
        }
        
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (board[r][c] == 'O') {
                    board[r][c] = 'X';
                } else if (board[r][c] == '#') {
                    board[r][c] = 'O';
                }
            }
        }
    }
};
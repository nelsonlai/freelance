/*
 * Problem: Minesweeper
 * Difficulty: Medium
 * Tags: array, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <queue>

using namespace std;

class Solution {
private:
    vector<vector<int>> directions = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

public:
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        int m = board.size(), n = board[0].size();
        int row = click[0], col = click[1];
        
        if (board[row][col] == 'M') {
            board[row][col] = 'X';
            return board;
        }
        
        queue<vector<int>> q;
        q.push({row, col});
        board[row][col] = 'B';
        
        while (!q.empty()) {
            auto curr = q.front();
            q.pop();
            int r = curr[0], c = curr[1];
            int mines = 0;
            
            for (auto& dir : directions) {
                int nr = r + dir[0], nc = c + dir[1];
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && board[nr][nc] == 'M') {
                    mines++;
                }
            }
            
            if (mines > 0) {
                board[r][c] = '0' + mines;
            } else {
                for (auto& dir : directions) {
                    int nr = r + dir[0], nc = c + dir[1];
                    if (nr >= 0 && nr < m && nc >= 0 && nc < n && board[nr][nc] == 'E') {
                        board[nr][nc] = 'B';
                        q.push({nr, nc});
                    }
                }
            }
        }
        
        return board;
    }
};
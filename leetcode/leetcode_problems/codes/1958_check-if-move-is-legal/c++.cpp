/*
 * Problem: Check if Move is Legal
 * Difficulty: Medium
 * Tags: array, simulation
 * 
 * Approach: Check all 8 directions for valid line of opposite color ending with same color
 * Time Complexity: O(8 * n) where n is board size
 * Space Complexity: O(1)
 */

#include <vector>

using namespace std;

class Solution {
public:
    bool checkMove(vector<vector<char>>& board, int rMove, int cMove, char color) {
        vector<vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, 
                                          {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
        int rows = board.size();
        int cols = board[0].size();
        
        for (auto& dir : directions) {
            int r = rMove + dir[0];
            int c = cMove + dir[1];
            int count = 0;
            
            while (r >= 0 && r < rows && c >= 0 && c < cols) {
                if (board[r][c] == '.') {
                    break;
                }
                if (board[r][c] == color) {
                    if (count >= 1) {
                        return true;
                    }
                    break;
                }
                if (board[r][c] != color) {
                    count++;
                }
                r += dir[0];
                c += dir[1];
            }
        }
        
        return false;
    }
};
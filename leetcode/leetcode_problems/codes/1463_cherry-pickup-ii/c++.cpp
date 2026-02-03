/*
 * Problem: Cherry Pickup II
 * Difficulty: Hard
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        vector<vector<vector<int>>> dp(rows, vector<vector<int>>(cols, vector<int>(cols, INT_MIN)));
        dp[0][0][cols-1] = grid[0][0] + grid[0][cols-1];
        
        for (int row = 1; row < rows; row++) {
            for (int col1 = 0; col1 < cols; col1++) {
                for (int col2 = 0; col2 < cols; col2++) {
                    for (int d1 = -1; d1 <= 1; d1++) {
                        for (int d2 = -1; d2 <= 1; d2++) {
                            int prev_col1 = col1 - d1;
                            int prev_col2 = col2 - d2;
                            if (prev_col1 >= 0 && prev_col1 < cols && prev_col2 >= 0 && prev_col2 < cols) {
                                int cherries = grid[row][col1];
                                if (col1 != col2) {
                                    cherries += grid[row][col2];
                                }
                                if (dp[row-1][prev_col1][prev_col2] != INT_MIN) {
                                    dp[row][col1][col2] = max(
                                        dp[row][col1][col2],
                                        dp[row-1][prev_col1][prev_col2] + cherries
                                    );
                                }
                            }
                        }
                    }
                }
            }
        }
        
        int result = INT_MIN;
        for (auto& row : dp[rows-1]) {
            for (int val : row) {
                result = max(result, val);
            }
        }
        return result;
    }
};
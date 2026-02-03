/*
 * Problem: Out of Boundary Paths
 * Difficulty: Medium
 * Tags: dp
 * 
 * Approach: Dynamic programming with memoization or tabulation
 * Time Complexity: O(n * m) where n and m are problem dimensions
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

class Solution {
private:
    int MOD = 1000000007;
    unordered_map<string, int> memo;
    
    int dp(int moves, int row, int col, int m, int n) {
        if (row < 0 || row >= m || col < 0 || col >= n) {
            return 1;
        }
        if (moves == 0) {
            return 0;
        }
        
        string key = to_string(moves) + "," + to_string(row) + "," + to_string(col);
        if (memo.find(key) != memo.end()) {
            return memo[key];
        }
        
        int result = 0;
        vector<vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        for (auto& dir : directions) {
            result = (result + dp(moves - 1, row + dir[0], col + dir[1], m, n)) % MOD;
        }
        
        memo[key] = result;
        return result;
    }

public:
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        return dp(maxMove, startRow, startColumn, m, n);
    }
};
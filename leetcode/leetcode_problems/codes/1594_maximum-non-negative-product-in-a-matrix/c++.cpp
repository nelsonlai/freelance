/*
 * Problem: Maximum Non Negative Product in a Matrix
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
private:
    static const int MOD = 1000000007;
    
public:
    int maxProductPath(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<long long>> dpMin(m, vector<long long>(n));
        vector<vector<long long>> dpMax(m, vector<long long>(n));
        
        dpMin[0][0] = dpMax[0][0] = grid[0][0];
        
        for (int i = 1; i < m; i++) {
            dpMin[i][0] = dpMax[i][0] = dpMin[i-1][0] * grid[i][0];
        }
        
        for (int j = 1; j < n; j++) {
            dpMin[0][j] = dpMax[0][j] = dpMin[0][j-1] * grid[0][j];
        }
        
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                long long val = grid[i][j];
                long long candidates[] = {
                    dpMin[i-1][j] * val,
                    dpMax[i-1][j] * val,
                    dpMin[i][j-1] * val,
                    dpMax[i][j-1] * val
                };
                dpMin[i][j] = min({candidates[0], candidates[1], candidates[2], candidates[3]});
                dpMax[i][j] = max({candidates[0], candidates[1], candidates[2], candidates[3]});
            }
        }
        
        return dpMax[m-1][n-1] >= 0 ? (int)(dpMax[m-1][n-1] % MOD) : -1;
    }
};
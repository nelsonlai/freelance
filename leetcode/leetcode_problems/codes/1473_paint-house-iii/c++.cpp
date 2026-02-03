/*
 * Problem: Paint House III
 * Difficulty: Hard
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

class Solution {
public:
    int minCost(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target) {
        vector<vector<vector<int>>> dp(m + 1, vector<vector<int>>(n + 1, vector<int>(target + 1, INT_MAX)));
        dp[0][0][0] = 0;
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (houses[i - 1] != 0 && houses[i - 1] != j) {
                    continue;
                }
                
                int paintCost = (houses[i - 1] == j) ? 0 : cost[i - 1][j - 1];
                
                for (int k = 1; k <= target; k++) {
                    for (int prevColor = 0; prevColor <= n; prevColor++) {
                        if (prevColor == j) {
                            if (dp[i - 1][j][k] != INT_MAX) {
                                dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j][k] + paintCost);
                            }
                        } else {
                            if (dp[i - 1][prevColor][k - 1] != INT_MAX) {
                                dp[i][j][k] = min(dp[i][j][k], dp[i - 1][prevColor][k - 1] + paintCost);
                            }
                        }
                    }
                }
            }
        }
        
        int result = INT_MAX;
        for (int j = 1; j <= n; j++) {
            result = min(result, dp[m][j][target]);
        }
        
        return result == INT_MAX ? -1 : result;
    }
};
/*
 * Problem: Burst Balloons
 * Difficulty: Hard
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        vector<int> extended(n + 2);
        extended[0] = 1;
        extended[n + 1] = 1;
        for (int i = 0; i < n; i++) {
            extended[i + 1] = nums[i];
        }
        
        vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));
        
        for (int length = 2; length < n + 2; length++) {
            for (int left = 0; left < n + 2 - length; left++) {
                int right = left + length;
                for (int i = left + 1; i < right; i++) {
                    dp[left][right] = max(dp[left][right],
                        extended[left] * extended[i] * extended[right] + 
                        dp[left][i] + dp[i][right]);
                }
            }
        }
        
        return dp[0][n + 1];
    }
};
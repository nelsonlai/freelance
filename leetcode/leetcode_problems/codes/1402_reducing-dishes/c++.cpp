/*
 * Problem: Reducing Dishes
 * Difficulty: Hard
 * Tags: array, dp, greedy, sort
 * 
 * Approach: Sort descending, use DP - dp[i][j] = max satisfaction using first i dishes, j cooked
 * Time Complexity: O(n^2) where n is number of dishes
 * Space Complexity: O(n) using rolling array
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxSatisfaction(vector<int>& satisfaction) {
        sort(satisfaction.begin(), satisfaction.end());
        int n = satisfaction.size();
        vector<int> dp(n + 1, 0);
        
        for (int i = n - 1; i >= 0; i--) {
            vector<int> newDp(n + 1, 0);
            for (int j = 1; j <= n - i; j++) {
                newDp[j] = max(dp[j], dp[j - 1] + satisfaction[i] * j);
            }
            dp = newDp;
        }
        
        int result = 0;
        for (int val : dp) {
            result = max(result, val);
        }
        return result;
    }
};
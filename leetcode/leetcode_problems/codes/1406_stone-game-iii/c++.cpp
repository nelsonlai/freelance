/*
 * Problem: Stone Game III
 * Difficulty: Hard
 * Tags: array, dp, math
 * 
 * Approach: DP - dp[i] = max score difference from position i, Alice wins if dp[0] > 0
 * Time Complexity: O(n) where n is length of stoneValue
 * Space Complexity: O(n) for DP table
 */

#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    string stoneGameIII(vector<int>& stoneValue) {
        int n = stoneValue.size();
        vector<int> dp(n + 1, INT_MIN);
        dp[n] = 0;
        
        for (int i = n - 1; i >= 0; i--) {
            int total = 0;
            for (int j = i; j < min(i + 3, n); j++) {
                total += stoneValue[j];
                dp[i] = max(dp[i], total - dp[j + 1]);
            }
        }
        
        if (dp[0] > 0) {
            return "Alice";
        } else if (dp[0] < 0) {
            return "Bob";
        } else {
            return "Tie";
        }
    }
};
/*
 * Problem: 4 Keys Keyboard
 * Difficulty: Medium
 * Tags: dp, math
 * 
 * Approach: Dynamic programming with memoization or tabulation
 * Time Complexity: O(n * m) where n and m are problem dimensions
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxA(int n) {
        vector<int> dp(n + 1, 0);
        
        for (int i = 1; i <= n; i++) {
            dp[i] = dp[i-1] + 1;
            
            for (int j = 3; j < i; j++) {
                dp[i] = max(dp[i], dp[i-j] * (j - 1));
            }
        }
        
        return dp[n];
    }
};
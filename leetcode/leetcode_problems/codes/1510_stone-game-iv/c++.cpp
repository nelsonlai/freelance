/*
 * Problem: Stone Game IV
 * Difficulty: Hard
 * Tags: dp, math
 * 
 * Approach: Dynamic programming with memoization or tabulation
 * Time Complexity: O(n * m) where n and m are problem dimensions
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>

using namespace std;

class Solution {
public:
    bool winnerSquareGame(int n) {
        vector<bool> dp(n + 1, false);
        
        for (int i = 1; i <= n; i++) {
            int j = 1;
            while (j * j <= i) {
                if (!dp[i - j * j]) {
                    dp[i] = true;
                    break;
                }
                j++;
            }
        }
        
        return dp[n];
    }
};
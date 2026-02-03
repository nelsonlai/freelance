/*
 * Problem: Guess Number Higher or Lower II
 * Difficulty: Medium
 * Tags: graph, dp, math
 * 
 * Approach: Dynamic programming with memoization or tabulation
 * Time Complexity: O(n * m) where n and m are problem dimensions
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int getMoneyAmount(int n) {
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        
        for (int length = 2; length <= n; length++) {
            for (int start = 1; start <= n - length + 1; start++) {
                int end = start + length - 1;
                dp[start][end] = INT_MAX;
                
                for (int guess = start; guess <= end; guess++) {
                    int cost = guess;
                    if (guess > start) {
                        cost += dp[start][guess - 1];
                    }
                    if (guess < end) {
                        cost += dp[guess + 1][end];
                    }
                    dp[start][end] = min(dp[start][end], cost);
                }
            }
        }
        
        return dp[1][n];
    }
};
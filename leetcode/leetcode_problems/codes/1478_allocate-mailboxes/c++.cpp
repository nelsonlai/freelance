/*
 * Problem: Allocate Mailboxes
 * Difficulty: Hard
 * Tags: array, tree, dp, math, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <algorithm>
#include <climits>
#include <vector>

using namespace std;

class Solution {
public:
    int minDistance(vector<int>& houses, int k) {
        sort(houses.begin(), houses.end());
        int n = houses.size();
        
        // cost[i][j] = min distance if one mailbox serves houses[i:j+1]
        vector<vector<int>> cost(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                int median = houses[(i + j) / 2];
                int sum = 0;
                for (int m = i; m <= j; m++) {
                    sum += abs(houses[m] - median);
                }
                cost[i][j] = sum;
            }
        }
        
        // dp[i][j] = min distance using j mailboxes for first i houses
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, INT_MAX));
        dp[0][0] = 0;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= min(i, k); j++) {
                for (int p = j - 1; p < i; p++) {
                    if (dp[p][j - 1] != INT_MAX) {
                        dp[i][j] = min(dp[i][j], dp[p][j - 1] + cost[p][i - 1]);
                    }
                }
            }
        }
        
        return dp[n][k];
    }
};
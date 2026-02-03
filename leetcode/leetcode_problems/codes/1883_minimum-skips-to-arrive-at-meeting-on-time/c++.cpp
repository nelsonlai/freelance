/*
 * Problem: Minimum Skips to Arrive at Meeting On Time
 * Difficulty: Hard
 * Tags: array, dp
 * 
 * Approach: DP - dp[i][j] = min time to reach i with j skips
 * Time Complexity: O(n^2) where n is length
 * Space Complexity: O(n^2)
 */

#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>

using namespace std;

class Solution {
public:
    int minSkips(vector<int>& dist, int speed, int hoursBefore) {
        int n = dist.size();
        vector<vector<double>> dp(n + 1, vector<double>(n + 1, 1e9));
        dp[0][0] = 0;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= i; j++) {
                if (j > 0) {
                    dp[i][j] = min(dp[i][j], dp[i-1][j-1] + (double)dist[i-1] / speed);
                }
                if (j < i) {
                    dp[i][j] = min(dp[i][j], ceil(dp[i-1][j] + (double)dist[i-1] / speed - 1e-9));
                }
            }
        }
        
        for (int j = 0; j <= n; j++) {
            if (dp[n][j] <= hoursBefore) {
                return j;
            }
        }
        
        return -1;
    }
};
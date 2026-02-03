/*
 * Problem: Maximum Number of Points with Cost
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: DP with optimization - track max from left and right
 * Time Complexity: O(m * n) where m, n are dimensions
 * Space Complexity: O(n)
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    long long maxPoints(vector<vector<int>>& points) {
        int m = points.size();
        int n = points[0].size();
        vector<long long> dp(n);
        for (int j = 0; j < n; j++) {
            dp[j] = points[0][j];
        }
        
        for (int i = 1; i < m; i++) {
            vector<long long> left(n);
            left[0] = dp[0];
            for (int j = 1; j < n; j++) {
                left[j] = max(left[j - 1] - 1, dp[j]);
            }
            
            vector<long long> right(n);
            right[n - 1] = dp[n - 1];
            for (int j = n - 2; j >= 0; j--) {
                right[j] = max(right[j + 1] - 1, dp[j]);
            }
            
            for (int j = 0; j < n; j++) {
                dp[j] = points[i][j] + max(left[j], right[j]);
            }
        }
        
        return *max_element(dp.begin(), dp.end());
    }
};
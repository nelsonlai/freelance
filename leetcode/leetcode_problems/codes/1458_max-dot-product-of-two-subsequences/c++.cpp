/*
 * Problem: Max Dot Product of Two Subsequences
 * Difficulty: Hard
 * Tags: array, dp
 * 
 * Approach: DP - dp[i][j] = max dot product using nums1[:i] and nums2[:j]
 * Time Complexity: O(n * m) where n, m are array lengths
 * Space Complexity: O(n * m) for DP table
 */

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        vector<vector<long long>> dp(m + 1, vector<long long>(n + 1, LLONG_MIN));
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                long long product = (long long) nums1[i-1] * nums2[j-1];
                dp[i][j] = max({
                    dp[i-1][j-1] + product,
                    dp[i-1][j],
                    dp[i][j-1],
                    product
                });
            }
        }
        
        return (int) dp[m][n];
    }
};
/*
 * Problem: Stone Game VIII
 * Difficulty: Hard
 * Tags: array, dp, math, prefix sum
 * 
 * Approach: DP - dp[i] = max score difference starting from position i
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n)
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int stoneGameVIII(vector<int>& stones) {
        int n = stones.size();
        vector<long long> prefix(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + stones[i];
        }
        
        vector<long long> dp(n, 0);
        dp[n - 1] = prefix[n];
        
        for (int i = n - 2; i > 0; i--) {
            dp[i] = max(prefix[i + 1] - dp[i + 1], dp[i + 1]);
        }
        
        return dp[1];
    }
};
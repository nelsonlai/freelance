/*
 * Problem: Minimum XOR Sum of Two Arrays
 * Difficulty: Hard
 * Tags: array, dp, bitmask
 * 
 * Approach: DP with bitmask - dp[mask] = min XOR sum using elements in mask
 * Time Complexity: O(n * 2^n) where n is length
 * Space Complexity: O(2^n)
 */

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int minimumXORSum(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        vector<int> dp(1 << n, INT_MAX);
        dp[0] = 0;
        
        for (int mask = 0; mask < (1 << n); mask++) {
            int count = __builtin_popcount(mask);
            if (count >= n) continue;
            
            for (int j = 0; j < n; j++) {
                if (!(mask & (1 << j))) {
                    int newMask = mask | (1 << j);
                    dp[newMask] = min(dp[newMask], dp[mask] + (nums1[count] ^ nums2[j]));
                }
            }
        }
        
        return dp[(1 << n) - 1];
    }
};
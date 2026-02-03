/*
 * Problem: Target Sum
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        unordered_map<int, int> dp;
        dp[0] = 1;
        
        for (int num : nums) {
            unordered_map<int, int> newDp;
            for (auto& entry : dp) {
                int sum = entry.first;
                int count = entry.second;
                newDp[sum + num] += count;
                newDp[sum - num] += count;
            }
            dp = newDp;
        }
        
        return dp[target];
    }
};
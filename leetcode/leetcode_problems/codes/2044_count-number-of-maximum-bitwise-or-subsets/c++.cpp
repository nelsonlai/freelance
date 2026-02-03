/*
 * Problem: Count Number of Maximum Bitwise-OR Subsets
 * Difficulty: Medium
 * Tags: array, bit manipulation, dp
 * 
 * Approach: Find max OR value, then count subsets with that OR value
 * Time Complexity: O(n * 2^n) or O(n * max_or) with DP
 * Space Complexity: O(max_or)
 */

#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int countMaxOrSubsets(vector<int>& nums) {
        // Find maximum OR value
        int maxOr = 0;
        for (int num : nums) {
            maxOr |= num;
        }
        
        // Count subsets with OR = max_or using DP
        int n = nums.size();
        // dp[mask] = number of ways to achieve OR = mask
        unordered_map<int, int> dp;
        dp[0] = 1;
        
        for (int num : nums) {
            unordered_map<int, int> newDp = dp;
            for (auto& [mask, count] : dp) {
                int newMask = mask | num;
                newDp[newMask] += count;
            }
            dp = newDp;
        }
        
        return dp[maxOr];
    }
};
/*
 * Problem: Largest Divisible Subset
 * Difficulty: Medium
 * Tags: array, dp, math, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        if (nums.empty()) {
            return {};
        }
        
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<int> dp(n, 1);
        vector<int> parent(n, -1);
        int maxLen = 1;
        int maxIdx = 0;
        
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] % nums[j] == 0 && dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    parent[i] = j;
                    if (dp[i] > maxLen) {
                        maxLen = dp[i];
                        maxIdx = i;
                    }
                }
            }
        }
        
        vector<int> result;
        int idx = maxIdx;
        while (idx != -1) {
            result.push_back(nums[idx]);
            idx = parent[idx];
        }
        
        reverse(result.begin(), result.end());
        return result;
    }
};
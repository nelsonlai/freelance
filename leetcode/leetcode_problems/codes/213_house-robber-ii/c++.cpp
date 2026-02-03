/*
 * Problem: House Robber II
 * Difficulty: Medium
 * Tags: array, tree, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    int robLinear(vector<int>& nums, int start, int end) {
        int prev2 = 0;
        int prev1 = 0;
        
        for (int i = start; i < end; i++) {
            int current = max(prev1, prev2 + nums[i]);
            prev2 = prev1;
            prev1 = current;
        }
        
        return prev1;
    }

public:
    int rob(vector<int>& nums) {
        if (nums.size() == 1) {
            return nums[0];
        }
        
        return max(robLinear(nums, 0, nums.size() - 1), 
                  robLinear(nums, 1, nums.size()));
    }
};
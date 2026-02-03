/*
 * Problem: Partition to K Equal Sum Subsets
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
private:
    bool backtrack(vector<int>& nums, vector<bool>& used, int start, int currentSum, int target, int remaining) {
        if (remaining == 0) {
            return true;
        }
        
        if (currentSum == target) {
            return backtrack(nums, used, 0, 0, target, remaining - 1);
        }
        
        for (int i = start; i < nums.size(); i++) {
            if (used[i] || currentSum + nums[i] > target) {
                continue;
            }
            
            used[i] = true;
            if (backtrack(nums, used, i + 1, currentSum + nums[i], target, remaining)) {
                return true;
            }
            used[i] = false;
            
            while (i + 1 < nums.size() && nums[i] == nums[i + 1]) {
                i++;
            }
        }
        
        return false;
    }

public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int total = accumulate(nums.begin(), nums.end(), 0);
        if (total % k != 0) {
            return false;
        }
        
        int target = total / k;
        sort(nums.rbegin(), nums.rend());
        vector<bool> used(nums.size(), false);
        
        return backtrack(nums, used, 0, 0, target, k);
    }
};
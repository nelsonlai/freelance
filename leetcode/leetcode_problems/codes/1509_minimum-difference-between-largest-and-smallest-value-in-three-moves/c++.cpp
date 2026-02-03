/*
 * Problem: Minimum Difference Between Largest and Smallest Value in Three Moves
 * Difficulty: Medium
 * Tags: array, greedy, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int minDifference(vector<int>& nums) {
        if (nums.size() <= 4) {
            return 0;
        }
        
        sort(nums.begin(), nums.end());
        int n = nums.size();
        
        int result = INT_MAX;
        for (int i = 0; i < 4; i++) {
            result = min(result, nums[n - 1 - (3 - i)] - nums[i]);
        }
        
        return result;
    }
};
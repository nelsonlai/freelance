/*
 * Problem: Maximum Difference Between Increasing Elements
 * Difficulty: Easy
 * Tags: array
 * 
 * Approach: Track minimum value seen so far, calculate max difference
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(1)
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maximumDifference(vector<int>& nums) {
        int minVal = nums[0];
        int maxDiff = -1;
        
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > minVal) {
                maxDiff = max(maxDiff, nums[i] - minVal);
            }
            minVal = min(minVal, nums[i]);
        }
        
        return maxDiff;
    }
};
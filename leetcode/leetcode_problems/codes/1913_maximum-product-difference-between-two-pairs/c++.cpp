/*
 * Problem: Maximum Product Difference Between Two Pairs
 * Difficulty: Easy
 * Tags: array, sort
 * 
 * Approach: Find two largest and two smallest numbers
 * Time Complexity: O(n) - can use partial sort
 * Space Complexity: O(1)
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxProductDifference(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        return nums[n - 1] * nums[n - 2] - nums[0] * nums[1];
    }
};
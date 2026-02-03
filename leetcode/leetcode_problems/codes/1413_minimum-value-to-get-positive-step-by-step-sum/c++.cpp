/*
 * Problem: Minimum Value to Get Positive Step by Step Sum
 * Difficulty: Easy
 * Tags: array
 * 
 * Approach: Track minimum prefix sum, return 1 - min_sum (if negative)
 * Time Complexity: O(n) where n is length of nums
 * Space Complexity: O(1)
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minStartValue(vector<int>& nums) {
        int minSum = 0;
        int prefixSum = 0;
        
        for (int num : nums) {
            prefixSum += num;
            minSum = min(minSum, prefixSum);
        }
        
        return minSum < 0 ? 1 - minSum : 1;
    }
};
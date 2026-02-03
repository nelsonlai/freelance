/*
 * Problem: Find the Middle Index in Array
 * Difficulty: Easy
 * Tags: array, prefix sum
 * 
 * Approach: Find index where left sum equals right sum
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(1)
 */

#include <vector>
#include <numeric>

using namespace std;

class Solution {
public:
    int findMiddleIndex(vector<int>& nums) {
        int total = accumulate(nums.begin(), nums.end(), 0);
        int leftSum = 0;
        
        for (int i = 0; i < nums.size(); i++) {
            if (leftSum == total - leftSum - nums[i]) {
                return i;
            }
            leftSum += nums[i];
        }
        
        return -1;
    }
};
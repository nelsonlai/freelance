/*
 * Problem: Longest Continuous Increasing Subsequence
 * Difficulty: Easy
 * Tags: array, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }
        
        int maxLength = 1;
        int currentLength = 1;
        
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > nums[i-1]) {
                currentLength++;
                maxLength = max(maxLength, currentLength);
            } else {
                currentLength = 1;
            }
        }
        
        return maxLength;
    }
};
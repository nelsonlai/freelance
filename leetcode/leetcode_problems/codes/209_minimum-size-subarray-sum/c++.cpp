/*
 * Problem: Minimum Size Subarray Sum
 * Difficulty: Medium
 * Tags: array, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int left = 0;
        int minLength = INT_MAX;
        int currentSum = 0;
        
        for (int right = 0; right < nums.size(); right++) {
            currentSum += nums[right];
            
            while (currentSum >= target) {
                minLength = min(minLength, right - left + 1);
                currentSum -= nums[left];
                left++;
            }
        }
        
        return minLength == INT_MAX ? 0 : minLength;
    }
};
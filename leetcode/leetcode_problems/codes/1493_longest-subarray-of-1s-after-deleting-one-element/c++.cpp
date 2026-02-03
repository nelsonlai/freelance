/*
 * Problem: Longest Subarray of 1's After Deleting One Element
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int left = 0;
        int zeros = 0;
        int maxLen = 0;
        
        for (int right = 0; right < nums.size(); right++) {
            if (nums[right] == 0) {
                zeros++;
            }
            
            while (zeros > 1) {
                if (nums[left] == 0) {
                    zeros--;
                }
                left++;
            }
            
            maxLen = max(maxLen, right - left);
        }
        
        return maxLen;
    }
};
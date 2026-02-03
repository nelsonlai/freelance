/*
 * Problem: Shuffle the Array
 * Difficulty: Easy
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
public:
    vector<int> shuffle(vector<int>& nums, int n) {
        vector<int> result;
        for (int i = 0; i < n; i++) {
            result.push_back(nums[i]);
            result.push_back(nums[i + n]);
        }
        return result;
    }
};
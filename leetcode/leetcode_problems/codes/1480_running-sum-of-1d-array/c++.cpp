/*
 * Problem: Running Sum of 1d Array
 * Difficulty: Easy
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        vector<int> result;
        int prefix = 0;
        for (int num : nums) {
            prefix += num;
            result.push_back(prefix);
        }
        return result;
    }
};
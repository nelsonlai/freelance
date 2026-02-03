/*
 * Problem: Missing Ranges
 * Difficulty: Easy
 * Tags: array, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> findMissingRanges(vector<int>& nums, int lower, int upper) {
        vector<vector<int>> result;
        int prev = lower - 1;
        
        for (int num : nums) {
            if (prev + 1 < num) {
                result.push_back({prev + 1, num - 1});
            }
            prev = num;
        }
        
        if (prev < upper) {
            result.push_back({prev + 1, upper});
        }
        
        return result;
    }
};
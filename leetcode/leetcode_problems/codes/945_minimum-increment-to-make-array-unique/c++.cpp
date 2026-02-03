/*
 * Problem: Minimum Increment to Make Array Unique
 * Difficulty: Medium
 * Tags: array, greedy, sort
 * 
 * Approach: Sort array, then increment duplicates to next available value
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(1)
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minIncrementForUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int moves = 0;
        int expected = 0;
        
        for (int num : nums) {
            if (num < expected) {
                moves += expected - num;
            }
            expected = max(expected, num) + 1;
        }
        
        return moves;
    }
};
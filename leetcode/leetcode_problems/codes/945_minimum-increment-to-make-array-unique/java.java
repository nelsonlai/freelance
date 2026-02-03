/**
 * Problem: Minimum Increment to Make Array Unique
 * Difficulty: Medium
 * Tags: array, greedy, sort
 * 
 * Approach: Sort array, then increment duplicates to next available value
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(1)
 */

import java.util.*;

class Solution {
    public int minIncrementForUnique(int[] nums) {
        Arrays.sort(nums);
        int moves = 0;
        int expected = 0;
        
        for (int num : nums) {
            if (num < expected) {
                moves += expected - num;
            }
            expected = Math.max(expected, num) + 1;
        }
        
        return moves;
    }
}
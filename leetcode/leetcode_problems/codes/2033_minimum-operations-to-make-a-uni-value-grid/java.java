/**
 * Problem: Minimum Operations to Make a Uni-Value Grid
 * Difficulty: Medium
 * Tags: array, math, sort
 * 
 * Approach: Find median value, calculate operations needed to make all cells equal
 * Time Complexity: O(mn log(mn)) for sorting
 * Space Complexity: O(mn)
 */

import java.util.*;

class Solution {
    public int minOperations(int[][] grid, int x) {
        List<Integer> nums = new ArrayList<>();
        for (int[] row : grid) {
            for (int val : row) {
                nums.add(val);
            }
        }
        
        // Check if all can be made equal modulo x
        int remainder = nums.get(0) % x;
        for (int num : nums) {
            if (num % x != remainder) {
                return -1;
            }
        }
        
        // Normalize all numbers
        List<Integer> normalized = new ArrayList<>();
        for (int num : nums) {
            normalized.add((num - remainder) / x);
        }
        
        Collections.sort(normalized);
        int median = normalized.get(normalized.size() / 2);
        
        int result = 0;
        for (int num : normalized) {
            result += Math.abs(num - median);
        }
        
        return result;
    }
}
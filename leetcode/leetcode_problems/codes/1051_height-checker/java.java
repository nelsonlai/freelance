/**
 * Problem: Height Checker
 * Difficulty: Easy
 * Tags: array, sort
 * 
 * Approach: Sort expected heights, count mismatches
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(n) for sorted array
 */

import java.util.*;

class Solution {
    public int heightChecker(int[] heights) {
        int[] expected = heights.clone();
        Arrays.sort(expected);
        
        int count = 0;
        for (int i = 0; i < heights.length; i++) {
            if (heights[i] != expected[i]) {
                count++;
            }
        }
        
        return count;
    }
}
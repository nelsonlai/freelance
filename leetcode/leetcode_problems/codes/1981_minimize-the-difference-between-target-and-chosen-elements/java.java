/**
 * Problem: Minimize the Difference Between Target and Chosen Elements
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: DP - track all possible sums, find closest to target
 * Time Complexity: O(n * m * sum_range) where n is rows, m is cols
 * Space Complexity: O(sum_range)
 */

import java.util.*;

class Solution {
    public int minimizeTheDifference(int[][] mat, int target) {
        Set<Integer> possibleSums = new HashSet<>();
        possibleSums.add(0);
        
        for (int[] row : mat) {
            Set<Integer> newSums = new HashSet<>();
            int rowMin = Arrays.stream(row).min().getAsInt();
            int rowMax = Arrays.stream(row).max().getAsInt();
            
            for (int s : possibleSums) {
                for (int num : row) {
                    int newSum = s + num;
                    if (newSum <= target + rowMax) {
                        newSums.add(newSum);
                    }
                }
            }
            possibleSums = newSums;
        }
        
        int minDiff = Integer.MAX_VALUE;
        for (int s : possibleSums) {
            minDiff = Math.min(minDiff, Math.abs(s - target));
        }
        
        return minDiff;
    }
}
/**
 * Problem: Maximum Length of Pair Chain
 * Difficulty: Medium
 * Tags: array, dp, greedy, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    public int findLongestChain(int[][] pairs) {
        Arrays.sort(pairs, (a, b) -> a[1] - b[1]);
        int count = 0;
        int end = Integer.MIN_VALUE;
        
        for (int[] pair : pairs) {
            if (pair[0] > end) {
                count++;
                end = pair[1];
            }
        }
        
        return count;
    }
}
/**
 * Problem: Moving Stones Until Consecutive II
 * Difficulty: Medium
 * Tags: array, dp, math, sort
 * 
 * Approach: Sort stones, use sliding window to find min/max moves
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(1)
 */

import java.util.*;

class Solution {
    public int[] numMovesStonesII(int[] stones) {
        Arrays.sort(stones);
        int n = stones.length;
        
        // Maximum: move stones to fill gaps
        int maxMoves = Math.max(stones[n - 1] - stones[1] - n + 2, 
                               stones[n - 2] - stones[0] - n + 2);
        
        // Minimum: sliding window to find window with most stones
        int minMoves = n;
        int j = 0;
        for (int i = 0; i < n; i++) {
            while (j < n && stones[j] - stones[i] < n) {
                j++;
            }
            if (j - i == n - 1 && stones[j - 1] - stones[i] == n - 2) {
                minMoves = Math.min(minMoves, 2);
            } else {
                minMoves = Math.min(minMoves, n - (j - i));
            }
        }
        
        return new int[]{minMoves, maxMoves};
    }
}
/**
 * Problem: Relative Ranks
 * Difficulty: Easy
 * Tags: array, sort, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public String[] findRelativeRanks(int[] score) {
        int n = score.length;
        int[][] sorted = new int[n][2];
        for (int i = 0; i < n; i++) {
            sorted[i][0] = score[i];
            sorted[i][1] = i;
        }
        Arrays.sort(sorted, (a, b) -> Integer.compare(b[0], a[0]));
        
        String[] result = new String[n];
        String[] medals = {"Gold Medal", "Silver Medal", "Bronze Medal"};
        
        for (int rank = 0; rank < n; rank++) {
            int idx = sorted[rank][1];
            if (rank < 3) {
                result[idx] = medals[rank];
            } else {
                result[idx] = String.valueOf(rank + 1);
            }
        }
        
        return result;
    }
}
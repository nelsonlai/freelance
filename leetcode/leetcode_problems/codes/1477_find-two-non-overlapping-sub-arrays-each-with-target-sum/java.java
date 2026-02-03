/**
 * Problem: Find Two Non-overlapping Sub-arrays Each With Target Sum
 * Difficulty: Medium
 * Tags: array, dp, hash, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    public int minSumOfLengths(int[] arr, int target) {
        int n = arr.length;
        Map<Integer, Integer> prefix = new HashMap<>();
        prefix.put(0, -1);
        int[] best = new int[n];
        Arrays.fill(best, Integer.MAX_VALUE);
        int bestSoFar = Integer.MAX_VALUE;
        int result = Integer.MAX_VALUE;
        int currentSum = 0;
        
        for (int i = 0; i < n; i++) {
            currentSum += arr[i];
            if (prefix.containsKey(currentSum - target)) {
                int start = prefix.get(currentSum - target);
                int length = i - start;
                if (start >= 0) {
                    result = Math.min(result, best[start] + length);
                }
                bestSoFar = Math.min(bestSoFar, length);
            }
            
            best[i] = bestSoFar;
            prefix.put(currentSum, i);
        }
        
        return result == Integer.MAX_VALUE ? -1 : result;
    }
}
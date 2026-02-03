/**
 * Problem: Most Visited Sector in  a Circular Track
 * Difficulty: Easy
 * Tags: array, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public List<Integer> mostVisited(int n, int[] rounds) {
        int[] counts = new int[n + 1];
        
        for (int i = 0; i < rounds.length - 1; i++) {
            int start = rounds[i];
            int end = rounds[i + 1];
            
            if (start <= end) {
                for (int j = start; j <= end; j++) {
                    counts[j]++;
                }
            } else {
                for (int j = start; j <= n; j++) {
                    counts[j]++;
                }
                for (int j = 1; j <= end; j++) {
                    counts[j]++;
                }
            }
        }
        
        int maxCount = 0;
        for (int i = 1; i <= n; i++) {
            maxCount = Math.max(maxCount, counts[i]);
        }
        
        List<Integer> result = new ArrayList<>();
        for (int i = 1; i <= n; i++) {
            if (counts[i] == maxCount) {
                result.add(i);
            }
        }
        return result;
    }
}
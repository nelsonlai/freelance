/**
 * Problem: Russian Doll Envelopes
 * Difficulty: Hard
 * Tags: array, dp, sort, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    public int maxEnvelopes(int[][] envelopes) {
        Arrays.sort(envelopes, (a, b) -> {
            if (a[0] == b[0]) {
                return b[1] - a[1];
            }
            return a[0] - b[0];
        });
        
        List<Integer> dp = new ArrayList<>();
        for (int[] envelope : envelopes) {
            int height = envelope[1];
            int idx = Collections.binarySearch(dp, height);
            if (idx < 0) {
                idx = -(idx + 1);
            }
            if (idx == dp.size()) {
                dp.add(height);
            } else {
                dp.set(idx, height);
            }
        }
        
        return dp.size();
    }
}
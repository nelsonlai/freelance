/**
 * Problem: Remove Boxes
 * Difficulty: Hard
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    private Map<String, Integer> memo = new HashMap<>();
    
    public int removeBoxes(int[] boxes) {
        return dp(0, boxes.length - 1, 0, boxes);
    }
    
    private int dp(int i, int j, int k, int[] boxes) {
        if (i > j) {
            return 0;
        }
        
        String key = i + "," + j + "," + k;
        if (memo.containsKey(key)) {
            return memo.get(key);
        }
        
        while (i < j && boxes[i] == boxes[i + 1]) {
            i++;
            k++;
        }
        
        int result = (k + 1) * (k + 1) + dp(i + 1, j, 0, boxes);
        
        for (int m = i + 1; m <= j; m++) {
            if (boxes[m] == boxes[i]) {
                result = Math.max(result, dp(i + 1, m - 1, 0, boxes) + dp(m, j, k + 1, boxes));
            }
        }
        
        memo.put(key, result);
        return result;
    }
}
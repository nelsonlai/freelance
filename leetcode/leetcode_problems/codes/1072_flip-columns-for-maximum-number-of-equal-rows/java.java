/**
 * Problem: Flip Columns For Maximum Number of Equal Rows
 * Difficulty: Medium
 * Tags: array, hash
 * 
 * Approach: Count rows with same pattern (original or flipped)
 * Time Complexity: O(m * n) where m and n are dimensions
 * Space Complexity: O(m * n) for patterns
 */

import java.util.*;

class Solution {
    public int maxEqualRowsAfterFlips(int[][] matrix) {
        Map<String, Integer> patterns = new HashMap<>();
        
        for (int[] row : matrix) {
            StringBuilder pattern1 = new StringBuilder();
            StringBuilder pattern2 = new StringBuilder();
            for (int val : row) {
                pattern1.append(val);
                pattern2.append(1 - val);
            }
            patterns.put(pattern1.toString(), patterns.getOrDefault(pattern1.toString(), 0) + 1);
            patterns.put(pattern2.toString(), patterns.getOrDefault(pattern2.toString(), 0) + 1);
        }
        
        return Collections.max(patterns.values()) / 2;
    }
}
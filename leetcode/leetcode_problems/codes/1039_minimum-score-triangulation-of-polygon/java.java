/**
 * Problem: Minimum Score Triangulation of Polygon
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: DP - for each edge (i,j), try all possible triangles with vertex k
 * Time Complexity: O(n^3)
 * Space Complexity: O(n^2) for DP table
 */

import java.util.*;

class Solution {
    private Map<String, Integer> memo = new HashMap<>();
    
    public int minScoreTriangulation(int[] values) {
        return dp(0, values.length - 1, values);
    }
    
    private int dp(int i, int j, int[] values) {
        if (j - i < 2) {
            return 0;
        }
        
        String key = i + "," + j;
        if (memo.containsKey(key)) {
            return memo.get(key);
        }
        
        int result = Integer.MAX_VALUE;
        for (int k = i + 1; k < j; k++) {
            result = Math.min(result, values[i] * values[j] * values[k] + 
                            dp(i, k, values) + dp(k, j, values));
        }
        
        memo.put(key, result);
        return result;
    }
}
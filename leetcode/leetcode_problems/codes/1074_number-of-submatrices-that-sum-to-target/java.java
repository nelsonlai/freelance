/**
 * Problem: Number of Submatrices That Sum to Target
 * Difficulty: Hard
 * Tags: array, hash
 * 
 * Approach: For each row range, compute column prefix sums and use hash map
 * Time Complexity: O(m^2 * n) where m and n are dimensions
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public int numSubmatrixSumTarget(int[][] matrix, int target) {
        int m = matrix.length, n = matrix[0].length;
        int result = 0;
        
        for (int i = 0; i < m; i++) {
            int[] colSum = new int[n];
            for (int j = i; j < m; j++) {
                for (int k = 0; k < n; k++) {
                    colSum[k] += matrix[j][k];
                }
                
                Map<Integer, Integer> prefixSum = new HashMap<>();
                prefixSum.put(0, 1);
                int currentSum = 0;
                
                for (int k = 0; k < n; k++) {
                    currentSum += colSum[k];
                    result += prefixSum.getOrDefault(currentSum - target, 0);
                    prefixSum.put(currentSum, prefixSum.getOrDefault(currentSum, 0) + 1);
                }
            }
        }
        
        return result;
    }
}
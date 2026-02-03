/**
 * Problem: Max Sum of Rectangle No Larger Than K
 * Difficulty: Hard
 * Tags: array, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public int maxSumSubmatrix(int[][] matrix, int k) {
        int m = matrix.length;
        int n = matrix[0].length;
        int result = Integer.MIN_VALUE;
        
        for (int left = 0; left < n; left++) {
            int[] rowSum = new int[m];
            for (int right = left; right < n; right++) {
                for (int i = 0; i < m; i++) {
                    rowSum[i] += matrix[i][right];
                }
                
                TreeSet<Integer> prefixSum = new TreeSet<>();
                prefixSum.add(0);
                int currSum = 0;
                
                for (int sum : rowSum) {
                    currSum += sum;
                    Integer ceiling = prefixSum.ceiling(currSum - k);
                    if (ceiling != null) {
                        result = Math.max(result, currSum - ceiling);
                    }
                    prefixSum.add(currSum);
                }
            }
        }
        
        return result;
    }
}
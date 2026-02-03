/**
 * Problem: Maximum Matrix Sum
 * Difficulty: Medium
 * Tags: array, greedy
 * 
 * Approach: Can flip pairs of negatives, maximize sum by minimizing negatives
 * Time Complexity: O(n * m) where n, m are dimensions
 * Space Complexity: O(1)
 */

class Solution {
    public long maxMatrixSum(int[][] matrix) {
        long total = 0;
        long minAbs = Long.MAX_VALUE;
        int negativeCount = 0;
        
        for (int[] row : matrix) {
            for (int num : row) {
                total += Math.abs(num);
                minAbs = Math.min(minAbs, Math.abs(num));
                if (num < 0) {
                    negativeCount++;
                }
            }
        }
        
        if (negativeCount % 2 == 1) {
            total -= 2 * minAbs;
        }
        
        return total;
    }
}
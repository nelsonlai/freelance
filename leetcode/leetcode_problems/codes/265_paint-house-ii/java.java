/**
 * Problem: Paint House II
 * Difficulty: Hard
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

class Solution {
    public int minCostII(int[][] costs) {
        if (costs == null || costs.length == 0 || costs[0].length == 0) {
            return 0;
        }
        
        int n = costs.length;
        int k = costs[0].length;
        
        for (int i = 1; i < n; i++) {
            int min1 = Integer.MAX_VALUE, min2 = Integer.MAX_VALUE;
            int min1Idx = -1;
            
            for (int j = 0; j < k; j++) {
                if (costs[i - 1][j] < min1) {
                    min2 = min1;
                    min1 = costs[i - 1][j];
                    min1Idx = j;
                } else if (costs[i - 1][j] < min2) {
                    min2 = costs[i - 1][j];
                }
            }
            
            for (int j = 0; j < k; j++) {
                if (j == min1Idx) {
                    costs[i][j] += min2;
                } else {
                    costs[i][j] += min1;
                }
            }
        }
        
        int result = Integer.MAX_VALUE;
        for (int j = 0; j < k; j++) {
            result = Math.min(result, costs[n - 1][j]);
        }
        
        return result;
    }
}
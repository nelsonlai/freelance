/**
 * Problem: Range Addition II
 * Difficulty: Easy
 * Tags: array, math
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public int maxCount(int m, int n, int[][] ops) {
        if (ops.length == 0) {
            return m * n;
        }
        
        int minRow = Integer.MAX_VALUE;
        int minCol = Integer.MAX_VALUE;
        
        for (int[] op : ops) {
            minRow = Math.min(minRow, op[0]);
            minCol = Math.min(minCol, op[1]);
        }
        
        return minRow * minCol;
    }
}
/**
 * Problem: Best Meeting Point
 * Difficulty: Hard
 * Tags: array, math, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public int minTotalDistance(int[][] grid) {
        List<Integer> rows = new ArrayList<>();
        List<Integer> cols = new ArrayList<>();
        
        for (int i = 0; i < grid.length; i++) {
            for (int j = 0; j < grid[0].length; j++) {
                if (grid[i][j] == 1) {
                    rows.add(i);
                    cols.add(j);
                }
            }
        }
        
        Collections.sort(cols);
        int rowMedian = rows.get(rows.size() / 2);
        int colMedian = cols.get(cols.size() / 2);
        
        int distance = 0;
        for (int row : rows) {
            distance += Math.abs(row - rowMedian);
        }
        for (int col : cols) {
            distance += Math.abs(col - colMedian);
        }
        
        return distance;
    }
}
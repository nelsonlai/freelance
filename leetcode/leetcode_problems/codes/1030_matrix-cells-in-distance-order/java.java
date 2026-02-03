/**
 * Problem: Matrix Cells in Distance Order
 * Difficulty: Easy
 * Tags: array, math, sort
 * 
 * Approach: Generate all cells, sort by Manhattan distance from center
 * Time Complexity: O(rows * cols * log(rows * cols))
 * Space Complexity: O(rows * cols)
 */

import java.util.*;

class Solution {
    public int[][] allCellsDistOrder(int rows, int cols, int rCenter, int cCenter) {
        List<int[]> cells = new ArrayList<>();
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cells.add(new int[]{i, j});
            }
        }
        
        cells.sort((a, b) -> {
            int distA = Math.abs(a[0] - rCenter) + Math.abs(a[1] - cCenter);
            int distB = Math.abs(b[0] - rCenter) + Math.abs(b[1] - cCenter);
            return distA - distB;
        });
        
        return cells.toArray(new int[cells.size()][]);
    }
}
/**
 * Problem: Cyclically Rotating a Grid
 * Difficulty: Medium
 * Tags: array, simulation
 * 
 * Approach: Extract each layer, rotate, put back
 * Time Complexity: O(m * n) where m, n are dimensions
 * Space Complexity: O(m * n)
 */

import java.util.*;

class Solution {
    public int[][] rotateGrid(int[][] grid, int k) {
        int m = grid.length;
        int n = grid[0].length;
        int[][] result = new int[m][n];
        
        int layers = Math.min(m, n) / 2;
        
        for (int layer = 0; layer < layers; layer++) {
            List<Integer> elements = new ArrayList<>();
            
            // Extract layer
            for (int j = layer; j < n - layer; j++) {
                elements.add(grid[layer][j]);
            }
            for (int i = layer + 1; i < m - layer; i++) {
                elements.add(grid[i][n - 1 - layer]);
            }
            for (int j = n - 2 - layer; j >= layer; j--) {
                elements.add(grid[m - 1 - layer][j]);
            }
            for (int i = m - 2 - layer; i > layer; i--) {
                elements.add(grid[i][layer]);
            }
            
            // Rotate
            int rot = k % elements.size();
            Collections.rotate(elements, -rot);
            
            // Put back
            int idx = 0;
            for (int j = layer; j < n - layer; j++) {
                result[layer][j] = elements.get(idx++);
            }
            for (int i = layer + 1; i < m - layer; i++) {
                result[i][n - 1 - layer] = elements.get(idx++);
            }
            for (int j = n - 2 - layer; j >= layer; j--) {
                result[m - 1 - layer][j] = elements.get(idx++);
            }
            for (int i = m - 2 - layer; i > layer; i--) {
                result[i][layer] = elements.get(idx++);
            }
        }
        
        return result;
    }
}
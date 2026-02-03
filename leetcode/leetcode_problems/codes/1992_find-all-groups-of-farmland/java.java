/**
 * Problem: Find All Groups of Farmland
 * Difficulty: Medium
 * Tags: array, search, DFS/BFS
 * 
 * Approach: Find top-left corner, expand to find bottom-right corner
 * Time Complexity: O(m * n) where m, n are dimensions
 * Space Complexity: O(1)
 */

import java.util.*;

class Solution {
    public int[][] findFarmland(int[][] land) {
        List<int[]> result = new ArrayList<>();
        int m = land.length;
        int n = land[0].length;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (land[i][j] == 1) {
                    // Find top-left corner
                    if ((i == 0 || land[i-1][j] == 0) && (j == 0 || land[i][j-1] == 0)) {
                        // Find bottom-right corner
                        int r2 = i, c2 = j;
                        while (r2 + 1 < m && land[r2+1][j] == 1) {
                            r2++;
                        }
                        while (c2 + 1 < n && land[i][c2+1] == 1) {
                            c2++;
                        }
                        
                        result.add(new int[]{i, j, r2, c2});
                    }
                }
            }
        }
        
        return result.toArray(new int[result.size()][]);
    }
}
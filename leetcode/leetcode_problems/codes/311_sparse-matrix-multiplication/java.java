/**
 * Problem: Sparse Matrix Multiplication
 * Difficulty: Medium
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public int[][] multiply(int[][] mat1, int[][] mat2) {
        int m = mat1.length;
        int k = mat1[0].length;
        int n = mat2[0].length;
        
        Map<Integer, Map<Integer, Integer>> sparse1 = new HashMap<>();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < k; j++) {
                if (mat1[i][j] != 0) {
                    sparse1.putIfAbsent(i, new HashMap<>());
                    sparse1.get(i).put(j, mat1[i][j]);
                }
            }
        }
        
        Map<Integer, Map<Integer, Integer>> sparse2 = new HashMap<>();
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < n; j++) {
                if (mat2[i][j] != 0) {
                    sparse2.putIfAbsent(i, new HashMap<>());
                    sparse2.get(i).put(j, mat2[i][j]);
                }
            }
        }
        
        int[][] result = new int[m][n];
        for (int i : sparse1.keySet()) {
            for (int j : sparse1.get(i).keySet()) {
                if (sparse2.containsKey(j)) {
                    for (int l : sparse2.get(j).keySet()) {
                        result[i][l] += sparse1.get(i).get(j) * sparse2.get(j).get(l);
                    }
                }
            }
        }
        
        return result;
    }
}
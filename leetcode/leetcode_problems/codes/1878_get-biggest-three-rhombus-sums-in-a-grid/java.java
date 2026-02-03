/**
 * Problem: Get Biggest Three Rhombus Sums in a Grid
 * Difficulty: Medium
 * Tags: array, math, heap
 * 
 * Approach: For each center, try all possible rhombus sizes, use heap to track top 3
 * Time Complexity: O(m * n * min(m,n)) where m, n are dimensions
 * Space Complexity: O(1) excluding output
 */

import java.util.*;

class Solution {
    public int[] getBiggestThree(int[][] grid) {
        int m = grid.length;
        int n = grid[0].length;
        Set<Integer> sums = new HashSet<>();
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int maxSize = Math.min(Math.min(i + 1, m - i), Math.min(j + 1, n - j));
                for (int size = 0; size < maxSize; size++) {
                    int total = 0;
                    if (size == 0) {
                        total = grid[i][j];
                    } else {
                        total += grid[i - size][j];
                        total += grid[i + size][j];
                        total += grid[i][j - size];
                        total += grid[i][j + size];
                        
                        for (int k = 1; k < size; k++) {
                            total += grid[i - size + k][j - k];
                            total += grid[i - size + k][j + k];
                            total += grid[i + size - k][j - k];
                            total += grid[i + size - k][j + k];
                        }
                    }
                    sums.add(total);
                }
            }
        }
        
        PriorityQueue<Integer> heap = new PriorityQueue<>();
        for (int s : sums) {
            heap.offer(s);
            if (heap.size() > 3) {
                heap.poll();
            }
        }
        
        List<Integer> result = new ArrayList<>(heap);
        Collections.sort(result, Collections.reverseOrder());
        return result.stream().mapToInt(i -> i).toArray();
    }
}
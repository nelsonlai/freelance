/**
 * Problem: Kth Smallest Element in a Sorted Matrix
 * Difficulty: Medium
 * Tags: array, sort, search, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public int kthSmallest(int[][] matrix, int k) {
        int n = matrix.length;
        PriorityQueue<int[]> heap = new PriorityQueue<>((a, b) -> a[0] - b[0]);
        
        for (int i = 0; i < Math.min(k, n); i++) {
            heap.offer(new int[]{matrix[i][0], i, 0});
        }
        
        for (int i = 0; i < k - 1; i++) {
            int[] cell = heap.poll();
            int row = cell[1];
            int col = cell[2];
            if (col + 1 < n) {
                heap.offer(new int[]{matrix[row][col + 1], row, col + 1});
            }
        }
        
        return heap.poll()[0];
    }
}
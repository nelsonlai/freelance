/**
 * Problem: Find the Kth Smallest Sum of a Matrix With Sorted Rows
 * Difficulty: Hard
 * Tags: array, sort, search, queue, heap
 * 
 * Approach: Use heap to merge sorted rows, keep k smallest sums
 * Time Complexity: O(m * k * log(k)) where m is rows
 * Space Complexity: O(k) for heap
 */

import java.util.*;

class Solution {
    public int kthSmallest(int[][] mat, int k) {
        PriorityQueue<Integer> heap = new PriorityQueue<>(Collections.reverseOrder());
        heap.offer(0);
        
        for (int[] row : mat) {
            PriorityQueue<Integer> newHeap = new PriorityQueue<>(Collections.reverseOrder());
            for (int sumVal : heap) {
                for (int num : row) {
                    newHeap.offer(sumVal + num);
                    if (newHeap.size() > k) {
                        newHeap.poll();
                    }
                }
            }
            heap = newHeap;
        }
        
        return heap.peek();
    }
}
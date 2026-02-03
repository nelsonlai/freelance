/**
 * Problem: Last Stone Weight
 * Difficulty: Easy
 * Tags: array, queue, heap
 * 
 * Approach: Use max heap to always get two heaviest stones
 * Time Complexity: O(n log n)
 * Space Complexity: O(n) for heap
 */

import java.util.*;

class Solution {
    public int lastStoneWeight(int[] stones) {
        PriorityQueue<Integer> heap = new PriorityQueue<>(Collections.reverseOrder());
        for (int stone : stones) {
            heap.offer(stone);
        }
        
        while (heap.size() > 1) {
            int first = heap.poll();
            int second = heap.poll();
            
            if (first != second) {
                heap.offer(first - second);
            }
        }
        
        return heap.isEmpty() ? 0 : heap.poll();
    }
}
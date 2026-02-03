/**
 * Problem: Remove Stones to Minimize the Total
 * Difficulty: Medium
 * Tags: array, greedy, queue, heap
 * 
 * Approach: Use max heap to always remove from largest pile
 * Time Complexity: O(n log n + k log n) where n is piles
 * Space Complexity: O(n)
 */

import java.util.*;

class Solution {
    public int minStoneSum(int[] piles, int k) {
        PriorityQueue<Integer> heap = new PriorityQueue<>((a, b) -> b - a);
        for (int pile : piles) {
            heap.offer(pile);
        }
        
        for (int i = 0; i < k; i++) {
            int largest = heap.poll();
            int remove = largest / 2;
            heap.offer(largest - remove);
        }
        
        int sum = 0;
        while (!heap.isEmpty()) {
            sum += heap.poll();
        }
        return sum;
    }
}
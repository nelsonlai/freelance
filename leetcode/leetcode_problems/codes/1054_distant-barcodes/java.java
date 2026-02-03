/**
 * Problem: Distant Barcodes
 * Difficulty: Medium
 * Tags: array, greedy, hash, sort, queue, heap
 * 
 * Approach: Use max heap to alternate most frequent with second most frequent
 * Time Complexity: O(n log n)
 * Space Complexity: O(n) for heap
 */

import java.util.*;

class Solution {
    public int[] rearrangeBarcodes(int[] barcodes) {
        Map<Integer, Integer> count = new HashMap<>();
        for (int code : barcodes) {
            count.put(code, count.getOrDefault(code, 0) + 1);
        }
        
        PriorityQueue<int[]> heap = new PriorityQueue<>((a, b) -> b[1] - a[1]);
        for (Map.Entry<Integer, Integer> entry : count.entrySet()) {
            heap.offer(new int[]{entry.getKey(), entry.getValue()});
        }
        
        int[] result = new int[barcodes.length];
        int[] prev = null;
        int idx = 0;
        
        while (!heap.isEmpty()) {
            int[] curr = heap.poll();
            result[idx++] = curr[0];
            curr[1]--;
            
            if (prev != null && prev[1] > 0) {
                heap.offer(prev);
            }
            
            prev = curr[1] > 0 ? curr : null;
        }
        
        return result;
    }
}
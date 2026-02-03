/**
 * Problem: The Skyline Problem
 * Difficulty: Hard
 * Tags: array, tree, dp, sort, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    public List<List<Integer>> getSkyline(int[][] buildings) {
        List<int[]> events = new ArrayList<>();
        for (int[] building : buildings) {
            events.add(new int[]{building[0], -building[2], building[1]});
            events.add(new int[]{building[1], 0, 0});
        }
        
        events.sort((a, b) -> {
            if (a[0] != b[0]) return Integer.compare(a[0], b[0]);
            return Integer.compare(a[1], b[1]);
        });
        
        List<List<Integer>> result = new ArrayList<>();
        PriorityQueue<int[]> heap = new PriorityQueue<>((a, b) -> Integer.compare(b[0], a[0]));
        heap.offer(new int[]{0, Integer.MAX_VALUE});
        int prevHeight = 0;
        
        for (int[] event : events) {
            while (heap.peek()[1] <= event[0]) {
                heap.poll();
            }
            
            if (event[1] < 0) {
                heap.offer(new int[]{-event[1], event[2]});
            }
            
            int currentHeight = heap.peek()[0];
            if (currentHeight != prevHeight) {
                result.add(Arrays.asList(event[0], currentHeight));
                prevHeight = currentHeight;
            }
        }
        
        return result;
    }
}
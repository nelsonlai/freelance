/**
 * Problem: Avoid Flood in The City
 * Difficulty: Medium
 * Tags: array, greedy, hash, search, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public int[] avoidFlood(int[] rains) {
        int n = rains.length;
        int[] result = new int[n];
        Arrays.fill(result, -1);
        Map<Integer, Integer> fullLakes = new HashMap<>();
        PriorityQueue<Integer> dryDays = new PriorityQueue<>();
        
        for (int i = 0; i < n; i++) {
            int lake = rains[i];
            if (lake == 0) {
                dryDays.offer(i);
            } else {
                if (fullLakes.containsKey(lake)) {
                    if (dryDays.isEmpty()) {
                        return new int[0];
                    }
                    int dryDay = dryDays.poll();
                    if (dryDay < fullLakes.get(lake)) {
                        return new int[0];
                    }
                    result[dryDay] = lake;
                }
                fullLakes.put(lake, i);
            }
        }
        
        while (!dryDays.isEmpty()) {
            result[dryDays.poll()] = 1;
        }
        
        return result;
    }
}
/**
 * Problem: The Number of the Smallest Unoccupied Chair
 * Difficulty: Medium
 * Tags: array, hash, queue, heap
 * 
 * Approach: Use heap to track available chairs and occupied chairs
 * Time Complexity: O(n log n) where n is friends
 * Space Complexity: O(n)
 */

import java.util.*;

class Solution {
    public int smallestChair(int[][] times, int targetFriend) {
        int n = times.length;
        List<int[]> events = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            events.add(new int[]{times[i][0], 1, i});
            events.add(new int[]{times[i][1], 0, i});
        }
        
        events.sort((a, b) -> {
            if (a[0] != b[0]) return Integer.compare(a[0], b[0]);
            return Integer.compare(a[1], b[1]);
        });
        
        PriorityQueue<Integer> available = new PriorityQueue<>();
        for (int i = 0; i < n; i++) {
            available.offer(i);
        }
        
        Map<Integer, Integer> chairMap = new HashMap<>();
        
        for (int[] event : events) {
            int time = event[0];
            int type = event[1];
            int friend = event[2];
            
            if (type == 0) {  // leave
                int chair = chairMap.remove(friend);
                available.offer(chair);
            } else {  // arrive
                int chair = available.poll();
                chairMap.put(friend, chair);
                if (friend == targetFriend) {
                    return chair;
                }
            }
        }
        
        return -1;
    }
}
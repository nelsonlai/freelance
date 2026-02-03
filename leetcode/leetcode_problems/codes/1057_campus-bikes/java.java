/**
 * Problem: Campus Bikes
 * Difficulty: Medium
 * Tags: array, sort, queue, heap
 * 
 * Approach: Sort all worker-bike pairs by distance, assign greedily
 * Time Complexity: O(n * m * log(n * m)) where n is workers, m is bikes
 * Space Complexity: O(n * m) for pairs
 */

import java.util.*;

class Solution {
    public int[] assignBikes(int[][] workers, int[][] bikes) {
        List<int[]> pairs = new ArrayList<>();
        for (int i = 0; i < workers.length; i++) {
            for (int j = 0; j < bikes.length; j++) {
                int dist = manhattan(workers[i], bikes[j]);
                pairs.add(new int[]{dist, i, j});
            }
        }
        
        pairs.sort((a, b) -> {
            if (a[0] != b[0]) return a[0] - b[0];
            if (a[1] != b[1]) return a[1] - b[1];
            return a[2] - b[2];
        });
        
        Set<Integer> assignedWorkers = new HashSet<>();
        Set<Integer> assignedBikes = new HashSet<>();
        int[] result = new int[workers.length];
        
        for (int[] pair : pairs) {
            int worker = pair[1], bike = pair[2];
            if (!assignedWorkers.contains(worker) && !assignedBikes.contains(bike)) {
                result[worker] = bike;
                assignedWorkers.add(worker);
                assignedBikes.add(bike);
            }
        }
        
        return result;
    }
    
    private int manhattan(int[] p1, int[] p2) {
        return Math.abs(p1[0] - p2[0]) + Math.abs(p1[1] - p2[1]);
    }
}
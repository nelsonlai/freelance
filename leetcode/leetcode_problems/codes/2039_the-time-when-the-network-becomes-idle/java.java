/**
 * Problem: The Time When the Network Becomes Idle
 * Difficulty: Medium
 * Tags: array, graph, search, BFS
 * 
 * Approach: BFS to find shortest distances, calculate when each server becomes idle
 * Time Complexity: O(n + m) where n is nodes, m is edges
 * Space Complexity: O(n + m)
 */

import java.util.*;

class Solution {
    public int networkBecomesIdle(int[][] edges, int[] patience) {
        int n = patience.length;
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        
        for (int[] edge : edges) {
            graph.get(edge[0]).add(edge[1]);
            graph.get(edge[1]).add(edge[0]);
        }
        
        // BFS to find shortest distances from node 0
        int[] dist = new int[n];
        Arrays.fill(dist, -1);
        dist[0] = 0;
        Queue<Integer> queue = new LinkedList<>();
        queue.offer(0);
        
        while (!queue.isEmpty()) {
            int node = queue.poll();
            for (int neighbor : graph.get(node)) {
                if (dist[neighbor] == -1) {
                    dist[neighbor] = dist[node] + 1;
                    queue.offer(neighbor);
                }
            }
        }
        
        int maxTime = 0;
        
        for (int i = 1; i < n; i++) {
            int roundTrip = 2 * dist[i];
            int idleTime;
            
            // Calculate when last message is sent
            if (roundTrip <= patience[i]) {
                // No resend needed
                idleTime = roundTrip + 1;
            } else {
                // Last resend happens at: patience[i] * floor((roundTrip - 1) / patience[i])
                int lastSend = patience[i] * ((roundTrip - 1) / patience[i]);
                idleTime = lastSend + roundTrip + 1;
            }
            
            maxTime = Math.max(maxTime, idleTime);
        }
        
        return maxTime;
    }
}
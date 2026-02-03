/**
 * Problem: Second Minimum Time to Reach Destination
 * Difficulty: Hard
 * Tags: array, graph, search, BFS, Dijkstra
 * 
 * Approach: Modified BFS/Dijkstra to find second shortest path considering traffic lights
 * Time Complexity: O(n + m) where n is nodes, m is edges
 * Space Complexity: O(n + m)
 */

import java.util.*;

class Solution {
    public int secondMinimum(int n, int[][] edges, int time, int change) {
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i <= n; i++) {
            graph.add(new ArrayList<>());
        }
        
        for (int[] edge : edges) {
            int u = edge[0];
            int v = edge[1];
            graph.get(u).add(v);
            graph.get(v).add(u);
        }
        
        // dist[i][0] = shortest time to node i
        // dist[i][1] = second shortest time to node i
        int[][] dist = new int[n + 1][2];
        for (int i = 0; i <= n; i++) {
            Arrays.fill(dist[i], Integer.MAX_VALUE);
        }
        dist[1][0] = 0;
        
        Queue<int[]> queue = new LinkedList<>();
        queue.offer(new int[]{1, 0});
        
        while (!queue.isEmpty()) {
            int[] curr = queue.poll();
            int node = curr[0];
            int currentTime = curr[1];
            
            // Calculate wait time due to traffic light
            // Light changes every 2*change seconds
            if ((currentTime / change) % 2 == 1) {
                // Red light - wait until next green
                currentTime = ((currentTime / change) + 1) * change;
            }
            
            int nextTime = currentTime + time;
            
            for (int neighbor : graph.get(node)) {
                if (nextTime < dist[neighbor][0]) {
                    // New shortest path
                    dist[neighbor][1] = dist[neighbor][0];
                    dist[neighbor][0] = nextTime;
                    queue.offer(new int[]{neighbor, nextTime});
                } else if (nextTime > dist[neighbor][0] && nextTime < dist[neighbor][1]) {
                    // New second shortest path
                    dist[neighbor][1] = nextTime;
                    queue.offer(new int[]{neighbor, nextTime});
                }
            }
        }
        
        return dist[n][1];
    }
}
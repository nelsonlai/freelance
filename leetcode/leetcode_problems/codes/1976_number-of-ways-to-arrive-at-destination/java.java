/**
 * Problem: Number of Ways to Arrive at Destination
 * Difficulty: Medium
 * Tags: array, graph, dp, sort, Dijkstra
 * 
 * Approach: Dijkstra to find shortest paths, count ways using DP
 * Time Complexity: O((n + m) log n) where n is nodes, m is edges
 * Space Complexity: O(n + m)
 */

import java.util.*;

class Solution {
    private static final int MOD = 1000000007;
    
    public int countPaths(int n, int[][] roads) {
        List<List<int[]>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        
        for (int[] road : roads) {
            graph.get(road[0]).add(new int[]{road[1], road[2]});
            graph.get(road[1]).add(new int[]{road[0], road[2]});
        }
        
        long[] dist = new long[n];
        long[] ways = new long[n];
        Arrays.fill(dist, Long.MAX_VALUE);
        dist[0] = 0;
        ways[0] = 1;
        
        PriorityQueue<long[]> heap = new PriorityQueue<>((a, b) -> Long.compare(a[0], b[0]));
        heap.offer(new long[]{0, 0});
        
        while (!heap.isEmpty()) {
            long[] curr = heap.poll();
            long d = curr[0];
            int u = (int) curr[1];
            
            if (d > dist[u]) {
                continue;
            }
            
            for (int[] edge : graph.get(u)) {
                int v = edge[0];
                int time = edge[1];
                
                if (dist[u] + time < dist[v]) {
                    dist[v] = dist[u] + time;
                    ways[v] = ways[u];
                    heap.offer(new long[]{dist[v], v});
                } else if (dist[u] + time == dist[v]) {
                    ways[v] = (ways[v] + ways[u]) % MOD;
                }
            }
        }
        
        return (int) ways[n - 1];
    }
}

/**
 * Problem: Largest Color Value in a Directed Graph
 * Difficulty: Hard
 * Tags: array, string, graph, dp, topological sort
 * 
 * Approach: Topological sort with DP to track max color count per path
 * Time Complexity: O(n + m) where n is nodes, m is edges
 * Space Complexity: O(n + m)
 */

import java.util.*;

class Solution {
    public int largestPathValue(String colors, int[][] edges) {
        int n = colors.length();
        List<List<Integer>> graph = new ArrayList<>();
        int[] indegree = new int[n];
        
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        
        for (int[] edge : edges) {
            graph.get(edge[0]).add(edge[1]);
            indegree[edge[1]]++;
        }
        
        int[][] dp = new int[n][26];
        Queue<Integer> queue = new LinkedList<>();
        
        for (int i = 0; i < n; i++) {
            if (indegree[i] == 0) {
                queue.offer(i);
            }
        }
        
        int processed = 0;
        int result = 0;
        
        while (!queue.isEmpty()) {
            int node = queue.poll();
            processed++;
            
            int colorIdx = colors.charAt(node) - 'a';
            dp[node][colorIdx]++;
            result = Math.max(result, dp[node][colorIdx]);
            
            for (int neighbor : graph.get(node)) {
                for (int c = 0; c < 26; c++) {
                    dp[neighbor][c] = Math.max(dp[neighbor][c], dp[node][c]);
                }
                
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) {
                    queue.offer(neighbor);
                }
            }
        }
        
        return processed == n ? result : -1;
    }
}
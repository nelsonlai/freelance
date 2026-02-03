/**
 * Problem: All Paths from Source Lead to Destination
 * Difficulty: Medium
 * Tags: graph, sort
 * 
 * Approach: DFS with cycle detection - check all paths from source lead to destination
 * Time Complexity: O(V + E)
 * Space Complexity: O(V + E) for graph
 */

import java.util.*;

class Solution {
    public boolean leadsToDestination(int n, int[][] edges, int source, int destination) {
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            graph.get(edge[0]).add(edge[1]);
        }
        
        Map<Integer, Boolean> visited = new HashMap<>();
        return dfs(graph, source, destination, visited);
    }
    
    private boolean dfs(List<List<Integer>> graph, int node, int destination, Map<Integer, Boolean> visited) {
        if (visited.containsKey(node)) {
            return visited.get(node);
        }
        
        if (node == destination) {
            visited.put(node, true);
            return true;
        }
        
        if (graph.get(node).isEmpty()) {
            visited.put(node, false);
            return false;
        }
        
        visited.put(node, false); // Mark as visiting
        for (int neighbor : graph.get(node)) {
            if (!dfs(graph, neighbor, destination, visited)) {
                return false;
            }
        }
        
        visited.put(node, true);
        return true;
    }
}
/**
 * Problem: Graph Valid Tree
 * Difficulty: Medium
 * Tags: tree, graph, search
 * 
 * Approach: DFS or BFS traversal
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(h) for recursion stack where h is height
 */

import java.util.*;

class Solution {
    public boolean validTree(int n, int[][] edges) {
        if (edges.length != n - 1) {
            return false;
        }
        
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        
        for (int[] edge : edges) {
            graph.get(edge[0]).add(edge[1]);
            graph.get(edge[1]).add(edge[0]);
        }
        
        Set<Integer> visited = new HashSet<>();
        
        if (!dfs(0, -1, graph, visited)) {
            return false;
        }
        
        return visited.size() == n;
    }
    
    private boolean dfs(int node, int parent, List<List<Integer>> graph, Set<Integer> visited) {
        if (visited.contains(node)) {
            return false;
        }
        
        visited.add(node);
        for (int neighbor : graph.get(node)) {
            if (neighbor != parent) {
                if (!dfs(neighbor, node, graph, visited)) {
                    return false;
                }
            }
        }
        return true;
    }
}
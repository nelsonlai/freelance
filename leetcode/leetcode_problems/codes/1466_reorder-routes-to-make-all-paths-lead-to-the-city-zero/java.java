/**
 * Problem: Reorder Routes to Make All Paths Lead to the City Zero
 * Difficulty: Medium
 * Tags: tree, graph, search
 * 
 * Approach: DFS or BFS traversal
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(h) for recursion stack where h is height
 */

import java.util.*;

class Solution {
    public int minReorder(int n, int[][] connections) {
        List<List<int[]>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        
        for (int[] conn : connections) {
            int u = conn[0], v = conn[1];
            graph.get(u).add(new int[]{v, 1}); // original direction
            graph.get(v).add(new int[]{u, 0}); // reversed direction
        }
        
        return dfs(0, -1, graph);
    }
    
    private int dfs(int node, int parent, List<List<int[]>> graph) {
        int count = 0;
        for (int[] neighbor : graph.get(node)) {
            int next = neighbor[0];
            int isOriginal = neighbor[1];
            if (next != parent) {
                if (isOriginal == 1) {
                    count++;
                }
                count += dfs(next, node, graph);
            }
        }
        return count;
    }
}
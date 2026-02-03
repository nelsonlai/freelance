/**
 * Problem: Redundant Connection II
 * Difficulty: Hard
 * Tags: array, tree, graph, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

class Solution {
    public int[] findRedundantDirectedConnection(int[][] edges) {
        int n = edges.length;
        int[] parent = new int[n + 1];
        int[] candidate1 = null, candidate2 = null;
        
        for (int[] edge : edges) {
            int u = edge[0], v = edge[1];
            if (parent[v] != 0) {
                candidate1 = new int[]{parent[v], v};
                candidate2 = edge;
            } else {
                parent[v] = u;
            }
        }
        
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }
        
        for (int[] edge : edges) {
            if (candidate2 != null && edge[0] == candidate2[0] && edge[1] == candidate2[1]) {
                continue;
            }
            int u = edge[0], v = edge[1];
            if (find(parent, u) == find(parent, v)) {
                return candidate1 != null ? candidate1 : edge;
            }
            union(parent, u, v);
        }
        
        return candidate2;
    }
    
    private int find(int[] parent, int x) {
        if (parent[x] != x) {
            parent[x] = find(parent, parent[x]);
        }
        return parent[x];
    }
    
    private void union(int[] parent, int x, int y) {
        parent[find(parent, x)] = find(parent, y);
    }
}
/**
 * Problem: Remove Max Number of Edges to Keep Graph Fully Traversable
 * Difficulty: Hard
 * Tags: array, graph
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public int maxNumEdgesToRemove(int n, int[][] edges) {
        List<int[]> type3Edges = new ArrayList<>();
        List<int[]> type1Edges = new ArrayList<>();
        List<int[]> type2Edges = new ArrayList<>();
        
        for (int[] edge : edges) {
            int t = edge[0];
            int u = edge[1] - 1;
            int v = edge[2] - 1;
            if (t == 3) {
                type3Edges.add(new int[]{u, v});
            } else if (t == 1) {
                type1Edges.add(new int[]{u, v});
            } else {
                type2Edges.add(new int[]{u, v});
            }
        }
        
        int[] parent = new int[n];
        int[] rank = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 1;
        }
        
        int used = 0;
        for (int[] edge : type3Edges) {
            if (union(parent, rank, edge[0], edge[1])) {
                used++;
            }
        }
        
        int[] parent1 = parent.clone();
        int[] rank1 = rank.clone();
        int[] parent2 = parent.clone();
        int[] rank2 = rank.clone();
        
        for (int[] edge : type1Edges) {
            if (union(parent1, rank1, edge[0], edge[1])) {
                used++;
            }
        }
        
        for (int[] edge : type2Edges) {
            if (union(parent2, rank2, edge[0], edge[1])) {
                used++;
            }
        }
        
        if (rank1[find(parent1, 0)] != n || rank2[find(parent2, 0)] != n) {
            return -1;
        }
        
        return edges.length - used;
    }
    
    private int find(int[] parent, int x) {
        if (parent[x] != x) {
            parent[x] = find(parent, parent[x]);
        }
        return parent[x];
    }
    
    private boolean union(int[] parent, int[] rank, int x, int y) {
        int px = find(parent, x);
        int py = find(parent, y);
        if (px == py) {
            return false;
        }
        if (rank[px] < rank[py]) {
            int temp = px;
            px = py;
            py = temp;
        }
        parent[py] = px;
        rank[px] += rank[py];
        return true;
    }
}
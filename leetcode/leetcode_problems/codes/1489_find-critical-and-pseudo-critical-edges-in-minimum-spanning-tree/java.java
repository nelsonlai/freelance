/**
 * Problem: Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree
 * Difficulty: Hard
 * Tags: array, tree, graph, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

import java.util.*;

class UnionFind {
    private int[] parent;
    private int[] rank;
    
    public UnionFind(int n) {
        parent = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    public int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    public boolean union(int x, int y) {
        int px = find(x);
        int py = find(y);
        if (px == py) {
            return false;
        }
        if (rank[px] < rank[py]) {
            int temp = px;
            px = py;
            py = temp;
        }
        parent[py] = px;
        if (rank[px] == rank[py]) {
            rank[px]++;
        }
        return true;
    }
}

class Solution {
    public List<List<Integer>> findCriticalAndPseudoCriticalEdges(int n, int[][] edges) {
        int m = edges.length;
        List<int[]> edgesWithIndex = new ArrayList<>();
        for (int i = 0; i < m; i++) {
            edgesWithIndex.add(new int[]{edges[i][0], edges[i][1], edges[i][2], i});
        }
        edgesWithIndex.sort((a, b) -> Integer.compare(a[2], b[2]));
        
        int baseWeight = mstWeight(n, edgesWithIndex, -1, -1);
        List<Integer> critical = new ArrayList<>();
        List<Integer> pseudoCritical = new ArrayList<>();
        
        for (int i = 0; i < m; i++) {
            int weightWithout = mstWeight(n, edgesWithIndex, i, -1);
            if (weightWithout > baseWeight) {
                critical.add(edgesWithIndex.get(i)[3]);
            } else {
                int weightWith = mstWeight(n, edgesWithIndex, -1, i);
                if (weightWith == baseWeight) {
                    pseudoCritical.add(edgesWithIndex.get(i)[3]);
                }
            }
        }
        
        return Arrays.asList(critical, pseudoCritical);
    }
    
    private int mstWeight(int n, List<int[]> edges, int exclude, int include) {
        UnionFind uf = new UnionFind(n);
        int weight = 0;
        int count = 0;
        
        if (include != -1) {
            int[] edge = edges.get(include);
            if (uf.union(edge[0], edge[1])) {
                weight += edge[2];
                count++;
            }
        }
        
        for (int i = 0; i < edges.size(); i++) {
            if (i == exclude || i == include) {
                continue;
            }
            int[] edge = edges.get(i);
            if (uf.union(edge[0], edge[1])) {
                weight += edge[2];
                count++;
                if (count == n - 1) {
                    break;
                }
            }
        }
        
        return count == n - 1 ? weight : Integer.MAX_VALUE;
    }
}
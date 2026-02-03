/**
 * Problem: Min Cost to Connect All Points
 * Difficulty: Medium
 * Tags: array, tree, graph
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

import java.util.*;

class Solution {
    public int minCostConnectPoints(int[][] points) {
        int n = points.length;
        List<int[]> edges = new ArrayList<>();
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int cost = Math.abs(points[i][0] - points[j][0]) + Math.abs(points[i][1] - points[j][1]);
                edges.add(new int[]{cost, i, j});
            }
        }
        
        edges.sort((a, b) -> Integer.compare(a[0], b[0]));
        
        int[] parent = new int[n];
        int[] rank = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 1;
        }
        
        int result = 0;
        int count = 0;
        
        for (int[] edge : edges) {
            if (union(parent, rank, edge[1], edge[2])) {
                result += edge[0];
                count++;
                if (count == n - 1) {
                    break;
                }
            }
        }
        
        return result;
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
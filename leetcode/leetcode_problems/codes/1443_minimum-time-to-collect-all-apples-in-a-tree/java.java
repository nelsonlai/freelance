/**
 * Problem: Minimum Time to Collect All Apples in a Tree
 * Difficulty: Medium
 * Tags: array, tree, hash, search
 * 
 * Approach: DFS - return time needed for subtree, add 2 for each edge to visit
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(n) for tree
 */

import java.util.*;

class Solution {
    public int minTime(int n, int[][] edges, List<Boolean> hasApple) {
        List<List<Integer>> tree = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            tree.add(new ArrayList<>());
        }
        
        for (int[] edge : edges) {
            tree.get(edge[0]).add(edge[1]);
            tree.get(edge[1]).add(edge[0]);
        }
        
        return dfs(0, -1, tree, hasApple);
    }
    
    private int dfs(int node, int parent, List<List<Integer>> tree, List<Boolean> hasApple) {
        int totalTime = 0;
        for (int child : tree.get(node)) {
            if (child == parent) {
                continue;
            }
            int childTime = dfs(child, node, tree, hasApple);
            if (childTime > 0 || hasApple.get(child)) {
                totalTime += childTime + 2;
            }
        }
        return totalTime;
    }
}
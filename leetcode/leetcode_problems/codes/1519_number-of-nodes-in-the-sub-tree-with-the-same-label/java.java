/**
 * Problem: Number of Nodes in the Sub-Tree With the Same Label
 * Difficulty: Medium
 * Tags: array, string, tree, graph, hash, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

import java.util.*;

class Solution {
    public int[] countSubTrees(int n, int[][] edges, String labels) {
        List<List<Integer>> tree = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            tree.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            tree.get(edge[0]).add(edge[1]);
            tree.get(edge[1]).add(edge[0]);
        }
        
        int[] result = new int[n];
        dfs(0, -1, tree, labels, result);
        return result;
    }
    
    private int[] dfs(int node, int parent, List<List<Integer>> tree, String labels, int[] result) {
        int[] count = new int[26];
        count[labels.charAt(node) - 'a'] = 1;
        
        for (int child : tree.get(node)) {
            if (child != parent) {
                int[] childCount = dfs(child, node, tree, labels, result);
                for (int i = 0; i < 26; i++) {
                    count[i] += childCount[i];
                }
            }
        }
        
        result[node] = count[labels.charAt(node) - 'a'];
        return count;
    }
}
/**
 * Problem: Count Nodes With the Highest Score
 * Difficulty: Medium
 * Tags: array, tree, search, DFS
 * 
 * Approach: Build tree, calculate subtree sizes, compute scores for each node
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(n)
 */

import java.util.*;

class Solution {
    public int countHighestScoreNodes(int[] parents) {
        int n = parents.length;
        List<List<Integer>> children = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            children.add(new ArrayList<>());
        }
        
        // Build tree
        for (int i = 1; i < n; i++) {
            children.get(parents[i]).add(i);
        }
        
        // Calculate subtree sizes
        int[] subtreeSize = new int[n];
        dfs(0, children, subtreeSize);
        
        // Calculate scores
        long maxScore = 0;
        int count = 0;
        
        for (int i = 0; i < n; i++) {
            long score = 1;
            long remaining = n - 1;
            
            for (int child : children.get(i)) {
                score *= subtreeSize[child];
                remaining -= subtreeSize[child];
            }
            
            if (remaining > 0) {
                score *= remaining;
            }
            
            if (score > maxScore) {
                maxScore = score;
                count = 1;
            } else if (score == maxScore) {
                count++;
            }
        }
        
        return count;
    }
    
    private int dfs(int node, List<List<Integer>> children, int[] subtreeSize) {
        int size = 1;
        for (int child : children.get(node)) {
            size += dfs(child, children, subtreeSize);
        }
        subtreeSize[node] = size;
        return size;
    }
}
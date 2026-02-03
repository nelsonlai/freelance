/**
 * Problem: Number of Good Leaf Nodes Pairs
 * Difficulty: Medium
 * Tags: tree, graph, search
 * 
 * Approach: DFS - return list of distances to leaves, count pairs within distance
 * Time Complexity: O(n * distance^2) where n is number of nodes
 * Space Complexity: O(h) for recursion stack
 */

import java.util.*;

/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode() {}
 *     TreeNode(int val) { this.val = val; }
 *     TreeNode(int val, TreeNode left, TreeNode right) {
 *         this.val = val;
 *         this.left = left;
 *         this.right = right;
 *     }
 * }
 */
class Solution {
    private int count = 0;
    
    public int countPairs(TreeNode root, int distance) {
        count = 0;
        dfs(root, distance);
        return count;
    }
    
    private List<Integer> dfs(TreeNode node, int distance) {
        if (node == null) {
            return new ArrayList<>();
        }
        
        if (node.left == null && node.right == null) {
            return Arrays.asList(1);
        }
        
        List<Integer> leftDistances = dfs(node.left, distance);
        List<Integer> rightDistances = dfs(node.right, distance);
        
        for (int leftDist : leftDistances) {
            for (int rightDist : rightDistances) {
                if (leftDist + rightDist <= distance) {
                    count++;
                }
            }
        }
        
        List<Integer> result = new ArrayList<>();
        for (int d : leftDistances) {
            if (d + 1 < distance) {
                result.add(d + 1);
            }
        }
        for (int d : rightDistances) {
            if (d + 1 < distance) {
                result.add(d + 1);
            }
        }
        
        return result;
    }
}
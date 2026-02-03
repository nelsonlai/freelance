/**
 * Problem: Maximum Average Subtree
 * Difficulty: Medium
 * Tags: tree, search
 * 
 * Approach: DFS - calculate sum and count for each subtree, track maximum average
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(h) for recursion stack where h is height
 */

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
    private double maxAvg = 0.0;
    
    private int[] dfs(TreeNode node) {
        if (node == null) {
            return new int[]{0, 0}; // {sum, count}
        }
        
        int[] left = dfs(node.left);
        int[] right = dfs(node.right);
        
        int totalSum = left[0] + right[0] + node.val;
        int totalCount = left[1] + right[1] + 1;
        double avg = (double) totalSum / totalCount;
        maxAvg = Math.max(maxAvg, avg);
        
        return new int[]{totalSum, totalCount};
    }
    
    public double maximumAverageSubtree(TreeNode root) {
        maxAvg = 0.0;
        dfs(root);
        return maxAvg;
    }
}

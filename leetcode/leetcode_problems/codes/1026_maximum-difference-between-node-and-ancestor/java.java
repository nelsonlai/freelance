/**
 * Problem: Maximum Difference Between Node and Ancestor
 * Difficulty: Medium
 * Tags: tree, search
 * 
 * Approach: DFS - track min and max values in path, update max difference
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
    private int maxDiff = 0;
    
    public int maxAncestorDiff(TreeNode root) {
        dfs(root, root.val, root.val);
        return maxDiff;
    }
    
    private void dfs(TreeNode node, int minVal, int maxVal) {
        if (node == null) {
            return;
        }
        
        minVal = Math.min(minVal, node.val);
        maxVal = Math.max(maxVal, node.val);
        maxDiff = Math.max(maxDiff, maxVal - minVal);
        
        dfs(node.left, minVal, maxVal);
        dfs(node.right, minVal, maxVal);
    }
}
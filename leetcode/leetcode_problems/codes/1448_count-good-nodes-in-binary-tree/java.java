/**
 * Problem: Count Good Nodes in Binary Tree
 * Difficulty: Medium
 * Tags: tree, search
 * 
 * Approach: DFS - track max value from root, count nodes >= max
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(h) for recursion stack
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
    private int dfs(TreeNode node, int maxVal) {
        if (node == null) {
            return 0;
        }
        
        int count = node.val >= maxVal ? 1 : 0;
        int newMax = Math.max(maxVal, node.val);
        count += dfs(node.left, newMax);
        count += dfs(node.right, newMax);
        
        return count;
    }
    
    public int goodNodes(TreeNode root) {
        return dfs(root, root.val);
    }
}

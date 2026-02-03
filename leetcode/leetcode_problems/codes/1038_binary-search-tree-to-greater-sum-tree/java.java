/**
 * Problem: Binary Search Tree to Greater Sum Tree
 * Difficulty: Medium
 * Tags: tree, search
 * 
 * Approach: Reverse in-order traversal - accumulate sum from right to left
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
    private int sum = 0;
    
    public TreeNode bstToGst(TreeNode root) {
        dfs(root);
        return root;
    }
    
    private void dfs(TreeNode node) {
        if (node == null) {
            return;
        }
        dfs(node.right);
        sum += node.val;
        node.val = sum;
        dfs(node.left);
    }
}
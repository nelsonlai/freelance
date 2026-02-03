/**
 * Problem: Maximum Binary Tree II
 * Difficulty: Medium
 * Tags: tree
 * 
 * Approach: Insert val at rightmost path where it's greater than parent
 * Time Complexity: O(h) where h is height
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
    public TreeNode insertIntoMaxTree(TreeNode root, int val) {
        if (root == null || val > root.val) {
            TreeNode newNode = new TreeNode(val);
            newNode.left = root;
            return newNode;
        }
        
        root.right = insertIntoMaxTree(root.right, val);
        return root;
    }
}

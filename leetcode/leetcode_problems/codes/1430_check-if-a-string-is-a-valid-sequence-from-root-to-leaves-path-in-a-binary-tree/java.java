/**
 * Problem: Check If a String Is a Valid Sequence from Root to Leaves Path in a Binary Tree
 * Difficulty: Medium
 * Tags: array, string, tree, search
 * 
 * Approach: DFS - check if path matches array and ends at leaf
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
    private boolean dfs(TreeNode node, int[] arr, int idx) {
        if (node == null || idx >= arr.length || node.val != arr[idx]) {
            return false;
        }
        
        if (idx == arr.length - 1) {
            return node.left == null && node.right == null;
        }
        
        return dfs(node.left, arr, idx + 1) || dfs(node.right, arr, idx + 1);
    }
    
    public boolean isValidSequence(TreeNode root, int[] arr) {
        return dfs(root, arr, 0);
    }
}

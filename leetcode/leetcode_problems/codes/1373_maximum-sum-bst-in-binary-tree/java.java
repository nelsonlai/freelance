/**
 * Problem: Maximum Sum BST in Binary Tree
 * Difficulty: Hard
 * Tags: tree, dp, search
 * 
 * Approach: DFS - return (isBST, min, max, sum) for each subtree
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
    private int maxSum = 0;
    
    private int[] dfs(TreeNode node) {
        if (node == null) {
            return new int[]{1, Integer.MAX_VALUE, Integer.MIN_VALUE, 0};
        }
        
        int[] left = dfs(node.left);
        int[] right = dfs(node.right);
        
        if (left[0] == 1 && right[0] == 1 && left[2] < node.val && node.val < right[1]) {
            int totalSum = left[3] + right[3] + node.val;
            maxSum = Math.max(maxSum, totalSum);
            return new int[]{1, Math.min(left[1], node.val), Math.max(right[2], node.val), totalSum};
        }
        
        return new int[]{0, 0, 0, 0};
    }
    
    public int maxSumBST(TreeNode root) {
        dfs(root);
        return maxSum;
    }
}

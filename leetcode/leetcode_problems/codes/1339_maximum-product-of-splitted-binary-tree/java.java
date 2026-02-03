/**
 * Problem: Maximum Product of Splitted Binary Tree
 * Difficulty: Medium
 * Tags: tree, search
 * 
 * Approach: Calculate total sum, DFS to find subtree sums, maximize product
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
    private static final int MOD = 1_000_000_007;
    private long maxProduct = 0;
    private long total = 0;
    
    private long totalSum(TreeNode node) {
        if (node == null) {
            return 0;
        }
        return node.val + totalSum(node.left) + totalSum(node.right);
    }
    
    private long dfs(TreeNode node) {
        if (node == null) {
            return 0;
        }
        
        long subtreeSum = node.val + dfs(node.left) + dfs(node.right);
        long product = subtreeSum * (total - subtreeSum);
        maxProduct = Math.max(maxProduct, product);
        return subtreeSum;
    }
    
    public int maxProduct(TreeNode root) {
        total = totalSum(root);
        dfs(root);
        return (int) (maxProduct % MOD);
    }
}

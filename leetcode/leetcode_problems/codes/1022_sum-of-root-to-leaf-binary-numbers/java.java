/**
 * Problem: Sum of Root To Leaf Binary Numbers
 * Difficulty: Easy
 * Tags: tree, search
 * 
 * Approach: DFS - accumulate binary number from root to leaf, sum all leaf values
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
    private int total = 0;
    
    public int sumRootToLeaf(TreeNode root) {
        dfs(root, 0);
        return total;
    }
    
    private void dfs(TreeNode node, int current) {
        if (node == null) {
            return;
        }
        
        current = current * 2 + node.val;
        
        if (node.left == null && node.right == null) {
            total += current;
        } else {
            dfs(node.left, current);
            dfs(node.right, current);
        }
    }
}
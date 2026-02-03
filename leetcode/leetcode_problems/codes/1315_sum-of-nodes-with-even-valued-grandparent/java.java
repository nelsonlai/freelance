/**
 * Problem: Sum of Nodes with Even-Valued Grandparent
 * Difficulty: Medium
 * Tags: tree, dp, search
 * 
 * Approach: DFS - pass parent and grandparent values, sum if grandparent is even
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
    private int dfs(TreeNode node, Integer parent, Integer grandparent) {
        if (node == null) {
            return 0;
        }
        
        int total = 0;
        if (grandparent != null && grandparent % 2 == 0) {
            total += node.val;
        }
        
        total += dfs(node.left, node.val, parent);
        total += dfs(node.right, node.val, parent);
        return total;
    }
    
    public int sumEvenGrandparent(TreeNode root) {
        return dfs(root, null, null);
    }
}

/**
 * Problem: Longest ZigZag Path in a Binary Tree
 * Difficulty: Medium
 * Tags: tree, dp, search
 * 
 * Approach: DFS - track longest path going left and right from each node
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
    private int maxPath = 0;
    
    private void dfs(TreeNode node, boolean goLeft, int length) {
        if (node == null) {
            return;
        }
        
        maxPath = Math.max(maxPath, length);
        
        if (goLeft) {
            dfs(node.left, false, length + 1);
            dfs(node.right, true, 1);
        } else {
            dfs(node.right, true, length + 1);
            dfs(node.left, false, 1);
        }
    }
    
    public int longestZigZag(TreeNode root) {
        dfs(root, true, 0);
        dfs(root, false, 0);
        return maxPath;
    }
}

/**
 * Problem: Binary Tree Coloring Game
 * Difficulty: Medium
 * Tags: tree, search
 * 
 * Approach: Find node x, calculate sizes of left, right, and parent subtrees
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
    private int leftSize = 0;
    private int rightSize = 0;
    
    private int dfs(TreeNode node, int x) {
        if (node == null) {
            return 0;
        }
        
        int left = dfs(node.left, x);
        int right = dfs(node.right, x);
        
        if (node.val == x) {
            leftSize = left;
            rightSize = right;
        }
        
        return left + right + 1;
    }
    
    public boolean btreeGameWinningMove(TreeNode root, int n, int x) {
        leftSize = 0;
        rightSize = 0;
        dfs(root, x);
        int parentSize = n - leftSize - rightSize - 1;
        
        return Math.max(Math.max(leftSize, rightSize), parentSize) > n / 2;
    }
}

/**
 * Problem: Largest BST Subtree
 * Difficulty: Medium
 * Tags: tree, dp, search
 * 
 * Approach: DFS or BFS traversal
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(n) or O(n * m) for DP table
 */

/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode() {
        // TODO: Implement optimized solution
        return 0;
    }
 *     TreeNode(int val) { this.val = val; }
 *     TreeNode(int val, TreeNode left, TreeNode right) {
 *         this.val = val;
 *         this.left = left;
 *         this.right = right;
 *     }
 * }
 */
class Solution {
    public int largestBSTSubtree(TreeNode root) {
        return dfs(root)[0];
    }
    
    private int[] dfs(TreeNode node) {
        if (node == null) {
            return new int[]{0, Integer.MAX_VALUE, Integer.MIN_VALUE};
        }
        
        int[] left = dfs(node.left);
        int[] right = dfs(node.right);
        
        if (left[2] < node.val && node.val < right[1]) {
            return new int[]{left[0] + right[0] + 1, 
                            Math.min(left[1], node.val), 
                            Math.max(right[2], node.val)};
        }
        
        return new int[]{Math.max(left[0], right[0]), Integer.MIN_VALUE, Integer.MAX_VALUE};
    }
}
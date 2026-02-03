/**
 * Problem: Binary Tree Longest Consecutive Sequence
 * Difficulty: Medium
 * Tags: tree, search
 * 
 * Approach: DFS or BFS traversal
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(h) for recursion stack where h is height
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
    private int maxLength = 0;
    
    public int longestConsecutive(TreeNode root) {
        dfs(root, null, 0);
        return maxLength;
    }
    
    private void dfs(TreeNode node, Integer parentVal, int length) {
        if (node == null) {
            return;
        }
        
        if (parentVal != null && node.val == parentVal + 1) {
            length++;
        } else {
            length = 1;
        }
        
        maxLength = Math.max(maxLength, length);
        
        dfs(node.left, node.val, length);
        dfs(node.right, node.val, length);
    }
}
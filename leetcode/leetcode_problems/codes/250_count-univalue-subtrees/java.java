/**
 * Problem: Count Univalue Subtrees
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
    private int count = 0;
    
    public int countUnivalSubtrees(TreeNode root) {
        isUnival(root);
        return count;
    }
    
    private boolean isUnival(TreeNode node) {
        if (node == null) {
            return true;
        }
        
        boolean left = isUnival(node.left);
        boolean right = isUnival(node.right);
        
        if (!left || !right) {
            return false;
        }
        
        if (node.left != null && node.left.val != node.val) {
            return false;
        }
        if (node.right != null && node.right.val != node.val) {
            return false;
        }
        
        count++;
        return true;
    }
}
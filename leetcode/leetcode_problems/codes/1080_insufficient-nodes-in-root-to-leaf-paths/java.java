/**
 * Problem: Insufficient Nodes in Root to Leaf Paths
 * Difficulty: Medium
 * Tags: tree, search
 * 
 * Approach: DFS - remove nodes if all paths through them are insufficient
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
    public TreeNode sufficientSubset(TreeNode root, int limit) {
        int[] result = dfs(root, 0, limit);
        return result[0] == 1 ? root : null;
    }
    
    private int[] dfs(TreeNode node, int currentSum, int limit) {
        if (node == null) {
            return new int[]{0, currentSum};
        }
        
        currentSum += node.val;
        
        if (node.left == null && node.right == null) {
            return currentSum >= limit ? new int[]{1, currentSum} : new int[]{0, currentSum};
        }
        
        int[] leftResult = dfs(node.left, currentSum, limit);
        int[] rightResult = dfs(node.right, currentSum, limit);
        
        if (leftResult[0] == 0 && rightResult[0] == 0) {
            return new int[]{0, Math.max(leftResult[1], rightResult[1])};
        }
        
        if (leftResult[0] == 0) {
            node.left = null;
        }
        if (rightResult[0] == 0) {
            node.right = null;
        }
        
        return new int[]{1, Math.max(leftResult[1], rightResult[1])};
    }
}
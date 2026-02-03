/**
 * Problem: Count Nodes Equal to Sum of Descendants
 * Difficulty: Medium
 * Tags: tree, search, DFS
 * 
 * Approach: DFS to calculate sum of descendants, count nodes where val equals sum
 * Time Complexity: O(n) where n is nodes
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
    private int count = 0;
    
    public int equalToDescendants(TreeNode root) {
        dfs(root);
        return count;
    }
    
    private long dfs(TreeNode node) {
        if (node == null) {
            return 0;
        }
        
        long leftSum = dfs(node.left);
        long rightSum = dfs(node.right);
        long descendantsSum = leftSum + rightSum;
        
        if (node.val == descendantsSum) {
            count++;
        }
        
        return node.val + descendantsSum;
    }
}

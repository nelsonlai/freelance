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
    public int findSecondMinimumValue(TreeNode root) {
        if (root == null) {
            return -1;
        }
        
        long result = dfs(root, root.val);
        return result == Long.MAX_VALUE ? -1 : (int)result;
    }
    
    private long dfs(TreeNode node, int rootVal) {
        if (node == null) {
            return Long.MAX_VALUE;
        }
        
        if (node.val > rootVal) {
            return node.val;
        }
        
        long left = dfs(node.left, rootVal);
        long right = dfs(node.right, rootVal);
        
        return Math.min(left, right);
    }
}

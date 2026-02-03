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
    private int maxLength = 0;
    
    public int longestConsecutive(TreeNode root) {
        dfs(root);
        return maxLength;
    }
    
    private int[] dfs(TreeNode node) {
        if (node == null) {
            return new int[]{0, 0};
        }
        
        int inc = 1, dec = 1;
        
        if (node.left != null) {
            int[] left = dfs(node.left);
            if (node.val == node.left.val + 1) {
                inc = Math.max(inc, left[0] + 1);
            }
            if (node.val == node.left.val - 1) {
                dec = Math.max(dec, left[1] + 1);
            }
        }
        
        if (node.right != null) {
            int[] right = dfs(node.right);
            if (node.val == node.right.val + 1) {
                inc = Math.max(inc, right[0] + 1);
            }
            if (node.val == node.right.val - 1) {
                dec = Math.max(dec, right[1] + 1);
            }
        }
        
        maxLength = Math.max(maxLength, inc + dec - 1);
        return new int[]{inc, dec};
    }
}

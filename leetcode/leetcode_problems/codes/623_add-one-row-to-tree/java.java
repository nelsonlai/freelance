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
    public TreeNode addOneRow(TreeNode root, int val, int depth) {
        if (depth == 1) {
            TreeNode newRoot = new TreeNode(val);
            newRoot.left = root;
            return newRoot;
        }
        
        dfs(root, val, depth, 1);
        return root;
    }
    
    private void dfs(TreeNode node, int val, int targetDepth, int currentDepth) {
        if (node == null) {
            return;
        }
        
        if (currentDepth == targetDepth - 1) {
            TreeNode left = new TreeNode(val);
            TreeNode right = new TreeNode(val);
            left.left = node.left;
            right.right = node.right;
            node.left = left;
            node.right = right;
        } else {
            dfs(node.left, val, targetDepth, currentDepth + 1);
            dfs(node.right, val, targetDepth, currentDepth + 1);
        }
    }
}

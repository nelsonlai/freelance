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
    public TreeNode pruneTree(TreeNode root) {
        return hasOne(root) ? root : null;
    }
    
    private boolean hasOne(TreeNode node) {
        if (node == null) {
            return false;
        }
        boolean leftHas = hasOne(node.left);
        boolean rightHas = hasOne(node.right);
        if (!leftHas) {
            node.left = null;
        }
        if (!rightHas) {
            node.right = null;
        }
        return node.val == 1 || leftHas || rightHas;
    }
}

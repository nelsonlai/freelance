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
    public TreeNode subtreeWithAllDeepest(TreeNode root) {
        return dfs(root)[0];
    }
    
    private TreeNode[] dfs(TreeNode node) {
        if (node == null) {
            return new TreeNode[]{null, new TreeNode(0)};
        }
        TreeNode[] left = dfs(node.left);
        TreeNode[] right = dfs(node.right);
        int ldepth = left[1].val;
        int rdepth = right[1].val;
        if (ldepth > rdepth) {
            return new TreeNode[]{left[0], new TreeNode(ldepth + 1)};
        }
        if (rdepth > ldepth) {
            return new TreeNode[]{right[0], new TreeNode(rdepth + 1)};
        }
        return new TreeNode[]{node, new TreeNode(ldepth + 1)};
    }
}

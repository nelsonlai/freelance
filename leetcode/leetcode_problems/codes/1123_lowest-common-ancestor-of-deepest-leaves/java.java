/**
 * Problem: Lowest Common Ancestor of Deepest Leaves
 * Difficulty: Medium
 * Tags: tree, hash, search
 * 
 * Approach: DFS - return node and depth, LCA is node where left and right depths are equal
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
    private TreeNode[] dfs(TreeNode node) {
        if (node == null) {
            return new TreeNode[]{null, new TreeNode(0)}; // {node, depth}
        }
        
        TreeNode[] left = dfs(node.left);
        TreeNode[] right = dfs(node.right);
        int leftDepth = left[1].val;
        int rightDepth = right[1].val;
        
        if (leftDepth > rightDepth) {
            return new TreeNode[]{left[0], new TreeNode(leftDepth + 1)};
        } else if (rightDepth > leftDepth) {
            return new TreeNode[]{right[0], new TreeNode(rightDepth + 1)};
        } else {
            return new TreeNode[]{node, new TreeNode(leftDepth + 1)};
        }
    }
    
    public TreeNode lcaDeepestLeaves(TreeNode root) {
        TreeNode[] result = dfs(root);
        return result[0];
    }
}

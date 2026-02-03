/**
 * Problem: Construct Binary Search Tree from Preorder Traversal
 * Difficulty: Medium
 * Tags: array, tree, search, stack
 * 
 * Approach: Recursive - use upper bound to determine where to split left and right subtrees
 * Time Complexity: O(n)
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
    private int idx = 0;
    
    public TreeNode bstFromPreorder(int[] preorder) {
        return build(preorder, Integer.MAX_VALUE);
    }
    
    private TreeNode build(int[] preorder, int upperBound) {
        if (idx >= preorder.length || preorder[idx] > upperBound) {
            return null;
        }
        
        TreeNode node = new TreeNode(preorder[idx++]);
        node.left = build(preorder, node.val);
        node.right = build(preorder, upperBound);
        
        return node;
    }
}
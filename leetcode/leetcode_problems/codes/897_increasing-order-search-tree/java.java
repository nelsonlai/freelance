import java.util.*;

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
    public TreeNode increasingBST(TreeNode root) {
        List<Integer> values = new ArrayList<>();
        inorder(root, values);
        
        TreeNode result = new TreeNode(values.get(0));
        TreeNode current = result;
        for (int i = 1; i < values.size(); i++) {
            current.right = new TreeNode(values.get(i));
            current = current.right;
        }
        return result;
    }
    
    private void inorder(TreeNode node, List<Integer> values) {
        if (node == null) {
            return;
        }
        inorder(node.left, values);
        values.add(node.val);
        inorder(node.right, values);
    }
}

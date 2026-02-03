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
    public boolean leafSimilar(TreeNode root1, TreeNode root2) {
        List<Integer> leaves1 = getLeaves(root1);
        List<Integer> leaves2 = getLeaves(root2);
        return leaves1.equals(leaves2);
    }
    
    private List<Integer> getLeaves(TreeNode node) {
        List<Integer> result = new ArrayList<>();
        if (node == null) {
            return result;
        }
        if (node.left == null && node.right == null) {
            result.add(node.val);
            return result;
        }
        result.addAll(getLeaves(node.left));
        result.addAll(getLeaves(node.right));
        return result;
    }
}

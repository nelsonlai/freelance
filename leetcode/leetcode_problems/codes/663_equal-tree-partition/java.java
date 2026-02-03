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
    public boolean checkEqualTree(TreeNode root) {
        Set<Integer> seen = new HashSet<>();
        int total = getSum(root, seen);
        seen.remove(total);
        return total % 2 == 0 && seen.contains(total / 2);
    }
    
    private int getSum(TreeNode node, Set<Integer> seen) {
        if (node == null) {
            return 0;
        }
        
        int sum = node.val + getSum(node.left, seen) + getSum(node.right, seen);
        seen.add(sum);
        return sum;
    }
}

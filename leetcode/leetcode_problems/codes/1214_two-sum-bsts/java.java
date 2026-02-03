/**
 * Problem: Two Sum BSTs
 * Difficulty: Medium
 * Tags: array, tree, search, stack
 * 
 * Approach: Store values from one BST in set, search for complement in other BST
 * Time Complexity: O(n + m) where n, m are sizes of trees
 * Space Complexity: O(n) for set
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
import java.util.*;

class Solution {
    private void collectValues(TreeNode node, Set<Integer> values) {
        if (node == null) {
            return;
        }
        values.add(node.val);
        collectValues(node.left, values);
        collectValues(node.right, values);
    }
    
    private boolean searchComplement(TreeNode node, Set<Integer> complementSet, int target) {
        if (node == null) {
            return false;
        }
        if (complementSet.contains(target - node.val)) {
            return true;
        }
        return searchComplement(node.left, complementSet, target) 
            || searchComplement(node.right, complementSet, target);
    }
    
    public boolean twoSumBSTs(TreeNode root1, TreeNode root2, int target) {
        Set<Integer> values1 = new HashSet<>();
        collectValues(root1, values1);
        return searchComplement(root2, values1, target);
    }
}

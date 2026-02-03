/**
 * Problem: Balance a Binary Search Tree
 * Difficulty: Medium
 * Tags: tree, greedy, search
 * 
 * Approach: Inorder traversal to get sorted list, build balanced BST from middle
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(n) for sorted list
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
    private List<Integer> inorder(TreeNode node) {
        if (node == null) {
            return new ArrayList<>();
        }
        List<Integer> result = new ArrayList<>();
        result.addAll(inorder(node.left));
        result.add(node.val);
        result.addAll(inorder(node.right));
        return result;
    }
    
    private TreeNode buildBST(List<Integer> vals) {
        if (vals.isEmpty()) {
            return null;
        }
        int mid = vals.size() / 2;
        TreeNode node = new TreeNode(vals.get(mid));
        node.left = buildBST(vals.subList(0, mid));
        node.right = buildBST(vals.subList(mid + 1, vals.size()));
        return node;
    }
    
    public TreeNode balanceBST(TreeNode root) {
        List<Integer> sortedVals = inorder(root);
        return buildBST(sortedVals);
    }
}

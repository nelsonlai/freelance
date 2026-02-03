/**
 * Problem: Boundary of Binary Tree
 * Difficulty: Medium
 * Tags: tree, search
 * 
 * Approach: DFS or BFS traversal
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
import java.util.*;

class Solution {
    public List<Integer> boundaryOfBinaryTree(TreeNode root) {
        if (root == null) {
            return new ArrayList<>();
        }
        
        if (root.left == null && root.right == null) {
            return Arrays.asList(root.val);
        }
        
        List<Integer> result = new ArrayList<>();
        result.add(root.val);
        
        if (root.left != null) {
            leftBoundary(root.left, result);
        }
        leaves(root, result);
        if (root.right != null) {
            rightBoundary(root.right, result);
        }
        
        return result;
    }
    
    private void leftBoundary(TreeNode node, List<Integer> result) {
        if (node == null || (node.left == null && node.right == null)) {
            return;
        }
        result.add(node.val);
        if (node.left != null) {
            leftBoundary(node.left, result);
        } else {
            leftBoundary(node.right, result);
        }
    }
    
    private void leaves(TreeNode node, List<Integer> result) {
        if (node == null) {
            return;
        }
        if (node.left == null && node.right == null) {
            result.add(node.val);
            return;
        }
        leaves(node.left, result);
        leaves(node.right, result);
    }
    
    private void rightBoundary(TreeNode node, List<Integer> result) {
        if (node == null || (node.left == null && node.right == null)) {
            return;
        }
        if (node.right != null) {
            rightBoundary(node.right, result);
        } else {
            rightBoundary(node.left, result);
        }
        result.add(node.val);
    }
}
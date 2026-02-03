/**
 * Problem: Merge BSTs to Create Single BST
 * Difficulty: Hard
 * Tags: array, tree, hash, search, BST validation
 * 
 * Approach: Find root (not a leaf in other trees), merge trees, validate BST
 * Time Complexity: O(n * m) where n is trees, m is nodes
 * Space Complexity: O(n * m)
 */

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
    public TreeNode canMerge(List<TreeNode> trees) {
        Map<Integer, TreeNode> valToNode = new HashMap<>();
        Set<Integer> leafVals = new HashSet<>();
        
        for (TreeNode tree : trees) {
            valToNode.put(tree.val, tree);
            if (tree.left != null) {
                leafVals.add(tree.left.val);
            }
            if (tree.right != null) {
                leafVals.add(tree.right.val);
            }
        }
        
        TreeNode root = null;
        for (TreeNode tree : trees) {
            if (!leafVals.contains(tree.val)) {
                if (root != null) {
                    return null;
                }
                root = tree;
            }
        }
        
        if (root == null) {
            return null;
        }
        
        merge(root, valToNode);
        
        if (valToNode.size() > 1) {
            return null;
        }
        
        if (validate(root, Long.MIN_VALUE, Long.MAX_VALUE)) {
            return root;
        }
        return null;
    }
    
    private void merge(TreeNode node, Map<Integer, TreeNode> valToNode) {
        if (node == null) {
            return;
        }
        
        if (node.left != null && valToNode.containsKey(node.left.val)) {
            node.left = valToNode.remove(node.left.val);
            merge(node.left, valToNode);
        }
        
        if (node.right != null && valToNode.containsKey(node.right.val)) {
            node.right = valToNode.remove(node.right.val);
            merge(node.right, valToNode);
        }
    }
    
    private boolean validate(TreeNode node, long minVal, long maxVal) {
        if (node == null) {
            return true;
        }
        if (node.val <= minVal || node.val >= maxVal) {
            return false;
        }
        return validate(node.left, minVal, node.val) && 
               validate(node.right, node.val, maxVal);
    }
}

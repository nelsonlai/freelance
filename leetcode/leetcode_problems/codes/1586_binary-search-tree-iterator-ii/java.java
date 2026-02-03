/**
 * Problem: Binary Search Tree Iterator II
 * Difficulty: Medium
 * Tags: tree, search, stack
 * 
 * Approach: Store all nodes in list via inorder traversal, track current index
 * Time Complexity: O(n) for init, O(1) for operations
 * Space Complexity: O(n) for node list
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
class BSTIterator {
    private List<Integer> nodes;
    private int idx;

    public BSTIterator(TreeNode root) {
        nodes = new ArrayList<>();
        idx = -1;
        inorder(root);
    }
    
    private void inorder(TreeNode node) {
        if (node != null) {
            inorder(node.left);
            nodes.add(node.val);
            inorder(node.right);
        }
    }
    
    public boolean hasNext() {
        return idx < nodes.size() - 1;
    }
    
    public int next() {
        idx++;
        return nodes.get(idx);
    }
    
    public boolean hasPrev() {
        return idx > 0;
    }
    
    public int prev() {
        idx--;
        return nodes.get(idx);
    }
}

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator obj = new BSTIterator(root);
 * boolean param_1 = obj.hasNext();
 * int param_2 = obj.next();
 * boolean param_3 = obj.hasPrev();
 * int param_4 = obj.prev();
 */
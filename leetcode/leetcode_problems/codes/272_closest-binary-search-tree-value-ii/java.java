/**
 * Problem: Closest Binary Search Tree Value II
 * Difficulty: Hard
 * Tags: array, tree, search, stack, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
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
    public List<Integer> closestKValues(TreeNode root, double target, int k) {
        Deque<Integer> result = new ArrayDeque<>();
        inorder(root, target, k, result);
        return new ArrayList<>(result);
    }
    
    private void inorder(TreeNode node, double target, int k, Deque<Integer> result) {
        if (node == null) {
            return;
        }
        
        inorder(node.left, target, k, result);
        
        if (result.size() < k) {
            result.offerLast(node.val);
        } else {
            if (Math.abs(node.val - target) < Math.abs(result.peekFirst() - target)) {
                result.pollFirst();
                result.offerLast(node.val);
            } else {
                return;
            }
        }
        
        inorder(node.right, target, k, result);
    }
}
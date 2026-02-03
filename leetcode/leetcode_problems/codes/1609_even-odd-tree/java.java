/**
 * Problem: Even Odd Tree
 * Difficulty: Medium
 * Tags: tree, search
 * 
 * Approach: DFS or BFS traversal
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(h) for recursion stack where h is height
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
    public boolean isEvenOddTree(TreeNode root) {
        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);
        int level = 0;
        
        while (!queue.isEmpty()) {
            int size = queue.size();
            Integer prev = null;
            
            for (int i = 0; i < size; i++) {
                TreeNode node = queue.poll();
                
                if (level % 2 == 0) {
                    if (node.val % 2 == 0) {
                        return false;
                    }
                    if (prev != null && node.val <= prev) {
                        return false;
                    }
                } else {
                    if (node.val % 2 == 1) {
                        return false;
                    }
                    if (prev != null && node.val >= prev) {
                        return false;
                    }
                }
                
                prev = node.val;
                
                if (node.left != null) {
                    queue.offer(node.left);
                }
                if (node.right != null) {
                    queue.offer(node.right);
                }
            }
            
            level++;
        }
        
        return true;
    }
}
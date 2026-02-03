/**
 * Problem: Check Completeness of a Binary Tree
 * Difficulty: Medium
 * Tags: tree, search
 * 
 * Approach: BFS - check if all nodes before a null are non-null
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(n) for queue
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
    public boolean isCompleteTree(TreeNode root) {
        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);
        boolean seenNull = false;
        
        while (!queue.isEmpty()) {
            TreeNode node = queue.poll();
            
            if (node == null) {
                seenNull = true;
            } else {
                if (seenNull) {
                    return false;
                }
                queue.offer(node.left);
                queue.offer(node.right);
            }
        }
        
        return true;
    }
}

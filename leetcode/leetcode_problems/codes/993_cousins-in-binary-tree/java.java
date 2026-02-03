/**
 * Problem: Cousins in Binary Tree
 * Difficulty: Easy
 * Tags: tree, search
 * 
 * Approach: BFS - find depth and parent of x and y, check if same depth but different parents
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
    public boolean isCousins(TreeNode root, int x, int y) {
        TreeNode xParent = null, yParent = null;
        int xDepth = -1, yDepth = -1;
        
        Queue<Object[]> queue = new LinkedList<>();
        queue.offer(new Object[]{root, null, 0});
        
        while (!queue.isEmpty()) {
            Object[] item = queue.poll();
            TreeNode node = (TreeNode) item[0];
            TreeNode parent = (TreeNode) item[1];
            int depth = (Integer) item[2];
            
            if (node.val == x) {
                xParent = parent;
                xDepth = depth;
            }
            if (node.val == y) {
                yParent = parent;
                yDepth = depth;
            }
            
            if (node.left != null) {
                queue.offer(new Object[]{node.left, node, depth + 1});
            }
            if (node.right != null) {
                queue.offer(new Object[]{node.right, node, depth + 1});
            }
        }
        
        return xDepth == yDepth && xParent != yParent;
    }
}

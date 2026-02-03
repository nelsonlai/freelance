/**
 * Problem: Correct a Binary Tree
 * Difficulty: Medium
 * Tags: tree, hash, search
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
    public TreeNode correctBinaryTree(TreeNode root) {
        Queue<Object[]> queue = new LinkedList<>();
        Set<TreeNode> visited = new HashSet<>();
        queue.offer(new Object[]{root, null, false});
        visited.add(root);
        
        while (!queue.isEmpty()) {
            Object[] item = queue.poll();
            TreeNode node = (TreeNode) item[0];
            TreeNode parent = (TreeNode) item[1];
            Boolean isLeft = (Boolean) item[2];
            
            if (node.right != null) {
                if (visited.contains(node.right)) {
                    if (isLeft) {
                        parent.left = null;
                    } else {
                        parent.right = null;
                    }
                    return root;
                }
                visited.add(node.right);
                queue.offer(new Object[]{node.right, node, false});
            }
            
            if (node.left != null) {
                if (visited.contains(node.left)) {
                    node.left = null;
                    return root;
                }
                visited.add(node.left);
                queue.offer(new Object[]{node.left, node, true});
            }
        }
        
        return root;
    }
}
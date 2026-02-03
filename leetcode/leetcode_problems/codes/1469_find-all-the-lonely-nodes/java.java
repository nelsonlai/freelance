/**
 * Problem: Find All The Lonely Nodes
 * Difficulty: Easy
 * Tags: array, tree, search
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
    public List<Integer> getLonelyNodes(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        dfs(root, result);
        return result;
    }
    
    private void dfs(TreeNode node, List<Integer> result) {
        if (node == null) {
            return;
        }
        
        if (node.left != null && node.right == null) {
            result.add(node.left.val);
        } else if (node.right != null && node.left == null) {
            result.add(node.right.val);
        }
        
        dfs(node.left, result);
        dfs(node.right, result);
    }
}
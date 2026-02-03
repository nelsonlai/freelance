/**
 * Problem: Find Leaves of Binary Tree
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
    public List<List<Integer>> findLeaves(TreeNode root) {
        List<List<Integer>> result = new ArrayList<>();
        dfs(root, result);
        return result;
    }
    
    private int dfs(TreeNode node, List<List<Integer>> result) {
        if (node == null) {
            return -1;
        }
        
        int leftHeight = dfs(node.left, result);
        int rightHeight = dfs(node.right, result);
        int height = Math.max(leftHeight, rightHeight) + 1;
        
        if (height >= result.size()) {
            result.add(new ArrayList<>());
        }
        result.get(height).add(node.val);
        
        return height;
    }
}
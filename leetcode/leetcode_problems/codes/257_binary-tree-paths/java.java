/**
 * Problem: Binary Tree Paths
 * Difficulty: Easy
 * Tags: string, tree, search
 * 
 * Approach: String manipulation with hash map or two pointers
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
    public List<String> binaryTreePaths(TreeNode root) {
        List<String> result = new ArrayList<>();
        dfs(root, new ArrayList<>(), result);
        return result;
    }
    
    private void dfs(TreeNode node, List<String> path, List<String> result) {
        if (node == null) {
            return;
        }
        
        path.add(String.valueOf(node.val));
        
        if (node.left == null && node.right == null) {
            result.add(String.join("->", path));
        } else {
            dfs(node.left, path, result);
            dfs(node.right, path, result);
        }
        
        path.remove(path.size() - 1);
    }
}
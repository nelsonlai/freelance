/**
 * Problem: Print Binary Tree
 * Difficulty: Medium
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
    public List<List<String>> printTree(TreeNode root) {
        int height = getHeight(root);
        int width = (1 << height) - 1;
        List<List<String>> result = new ArrayList<>();
        
        for (int i = 0; i < height; i++) {
            List<String> row = new ArrayList<>();
            for (int j = 0; j < width; j++) {
                row.add("");
            }
            result.add(row);
        }
        
        fill(root, result, 0, 0, width - 1);
        return result;
    }
    
    private int getHeight(TreeNode node) {
        if (node == null) {
            return 0;
        }
        return 1 + Math.max(getHeight(node.left), getHeight(node.right));
    }
    
    private void fill(TreeNode node, List<List<String>> result, int level, int left, int right) {
        if (node == null) {
            return;
        }
        
        int mid = (left + right) / 2;
        result.get(level).set(mid, String.valueOf(node.val));
        fill(node.left, result, level + 1, left, mid - 1);
        fill(node.right, result, level + 1, mid + 1, right);
    }
}
/**
 * Problem: Delete Nodes And Return Forest
 * Difficulty: Medium
 * Tags: array, tree, hash, search
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
    public List<TreeNode> delNodes(TreeNode root, int[] to_delete) {
        Set<Integer> toDeleteSet = new HashSet<>();
        for (int val : to_delete) {
            toDeleteSet.add(val);
        }
        
        List<TreeNode> result = new ArrayList<>();
        dfs(root, true, toDeleteSet, result);
        return result;
    }
    
    private TreeNode dfs(TreeNode node, boolean isRoot, Set<Integer> toDeleteSet, List<TreeNode> result) {
        if (node == null) {
            return null;
        }
        
        boolean shouldDelete = toDeleteSet.contains(node.val);
        
        if (isRoot && !shouldDelete) {
            result.add(node);
        }
        
        node.left = dfs(node.left, shouldDelete, toDeleteSet, result);
        node.right = dfs(node.right, shouldDelete, toDeleteSet, result);
        
        return shouldDelete ? null : node;
    }
}
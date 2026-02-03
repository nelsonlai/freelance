/**
 * Problem: Find Duplicate Subtrees
 * Difficulty: Medium
 * Tags: tree, hash, search
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
    private Map<String, Integer> count = new HashMap<>();
    private List<TreeNode> result = new ArrayList<>();
    
    public List<TreeNode> findDuplicateSubtrees(TreeNode root) {
        serialize(root);
        return result;
    }
    
    private String serialize(TreeNode node) {
        if (node == null) {
            return "#";
        }
        
        String serial = node.val + "," + serialize(node.left) + "," + serialize(node.right);
        count.put(serial, count.getOrDefault(serial, 0) + 1);
        
        if (count.get(serial) == 2) {
            result.add(node);
        }
        
        return serial;
    }
}
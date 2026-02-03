/**
 * Problem: Path Sum III
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
 *     TreeNode() {
        // TODO: Implement optimized solution
        return 0;
    }
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
    public int pathSum(TreeNode root, int targetSum) {
        Map<Long, Integer> count = new HashMap<>();
        count.put(0L, 1);
        return dfs(root, 0, targetSum, count);
    }
    
    private int dfs(TreeNode node, long currentSum, int targetSum, Map<Long, Integer> count) {
        if (node == null) {
            return 0;
        }
        
        currentSum += node.val;
        int result = count.getOrDefault(currentSum - targetSum, 0);
        
        count.put(currentSum, count.getOrDefault(currentSum, 0) + 1);
        result += dfs(node.left, currentSum, targetSum, count);
        result += dfs(node.right, currentSum, targetSum, count);
        count.put(currentSum, count.get(currentSum) - 1);
        
        return result;
    }
}
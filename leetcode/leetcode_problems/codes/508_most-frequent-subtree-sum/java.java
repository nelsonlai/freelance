/**
 * Problem: Most Frequent Subtree Sum
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
    private Map<Integer, Integer> count = new HashMap<>();
    
    public int[] findFrequentTreeSum(TreeNode root) {
        dfs(root);
        
        if (count.isEmpty()) {
            return new int[0];
        }
        
        int maxCount = Collections.max(count.values());
        List<Integer> result = new ArrayList<>();
        for (Map.Entry<Integer, Integer> entry : count.entrySet()) {
            if (entry.getValue() == maxCount) {
                result.add(entry.getKey());
            }
        }
        
        return result.stream().mapToInt(i -> i).toArray();
    }
    
    private int dfs(TreeNode node) {
        if (node == null) {
            return 0;
        }
        
        int leftSum = dfs(node.left);
        int rightSum = dfs(node.right);
        int total = node.val + leftSum + rightSum;
        count.put(total, count.getOrDefault(total, 0) + 1);
        
        return total;
    }
}
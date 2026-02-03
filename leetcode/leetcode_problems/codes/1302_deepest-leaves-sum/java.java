/**
 * Problem: Deepest Leaves Sum
 * Difficulty: Medium
 * Tags: tree, search
 * 
 * Approach: BFS - find deepest level, sum all nodes at that level
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(n) for queue
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
    public int deepestLeavesSum(TreeNode root) {
        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);
        int levelSum = 0;
        
        while (!queue.isEmpty()) {
            levelSum = 0;
            int levelSize = queue.size();
            
            for (int i = 0; i < levelSize; i++) {
                TreeNode node = queue.poll();
                levelSum += node.val;
                
                if (node.left != null) {
                    queue.offer(node.left);
                }
                if (node.right != null) {
                    queue.offer(node.right);
                }
            }
        }
        
        return levelSum;
    }
}

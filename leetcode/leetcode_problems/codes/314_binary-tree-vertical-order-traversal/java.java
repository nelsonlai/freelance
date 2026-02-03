/**
 * Problem: Binary Tree Vertical Order Traversal
 * Difficulty: Medium
 * Tags: tree, hash, sort, search
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
    public List<List<Integer>> verticalOrder(TreeNode root) {
        if (root == null) {
            return new ArrayList<>();
        }
        
        Map<Integer, List<Integer>> columnMap = new TreeMap<>();
        Queue<Pair> queue = new LinkedList<>();
        queue.offer(new Pair(root, 0));
        
        while (!queue.isEmpty()) {
            Pair pair = queue.poll();
            TreeNode node = pair.node;
            int col = pair.col;
            
            columnMap.putIfAbsent(col, new ArrayList<>());
            columnMap.get(col).add(node.val);
            
            if (node.left != null) {
                queue.offer(new Pair(node.left, col - 1));
            }
            if (node.right != null) {
                queue.offer(new Pair(node.right, col + 1));
            }
        }
        
        return new ArrayList<>(columnMap.values());
    }
    
    class Pair {
        TreeNode node;
        int col;
        
        Pair(TreeNode node, int col) {
            this.node = node;
            this.col = col;
        }
    }
}
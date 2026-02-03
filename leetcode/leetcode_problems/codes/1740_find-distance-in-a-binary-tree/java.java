/**
 * Problem: Find Distance in a Binary Tree
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
class Solution {
    private TreeNode findLCA(TreeNode node, int p, int q) {
        if (node == null || node.val == p || node.val == q) {
            return node;
        }
        
        TreeNode left = findLCA(node.left, p, q);
        TreeNode right = findLCA(node.right, p, q);
        
        if (left != null && right != null) {
            return node;
        }
        return left != null ? left : right;
    }
    
    private int distance(TreeNode node, int target, int dist) {
        if (node == null) {
            return -1;
        }
        if (node.val == target) {
            return dist;
        }
        
        int left = distance(node.left, target, dist + 1);
        if (left != -1) {
            return left;
        }
        return distance(node.right, target, dist + 1);
    }
    
    public int findDistance(TreeNode root, int p, int q) {
        TreeNode lca = findLCA(root, p, q);
        return distance(lca, p, 0) + distance(lca, q, 0);
    }
}
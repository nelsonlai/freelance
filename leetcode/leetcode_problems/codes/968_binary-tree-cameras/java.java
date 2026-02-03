/**
 * Problem: Binary Tree Cameras
 * Difficulty: Hard
 * Tags: tree, dp, search
 * 
 * Approach: Greedy DFS - place cameras at parent of uncovered leaves
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
    private int cameras = 0;
    
    // 0: uncovered, 1: covered, 2: has camera
    public int minCameraCover(TreeNode root) {
        if (dfs(root) == 0) {
            cameras++;
        }
        return cameras;
    }
    
    private int dfs(TreeNode node) {
        if (node == null) {
            return 1; // covered
        }
        
        int left = dfs(node.left);
        int right = dfs(node.right);
        
        if (left == 0 || right == 0) {
            cameras++;
            return 2; // place camera
        }
        
        if (left == 2 || right == 2) {
            return 1; // covered by child camera
        }
        
        return 0; // uncovered
    }
}

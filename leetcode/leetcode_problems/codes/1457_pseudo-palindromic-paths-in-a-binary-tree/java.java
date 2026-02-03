/**
 * Problem: Pseudo-Palindromic Paths in a Binary Tree
 * Difficulty: Medium
 * Tags: string, tree, search
 * 
 * Approach: DFS - track digit counts, check if at most one odd count at leaf
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(h) for recursion stack
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
    private int dfs(TreeNode node, int[] count) {
        if (node == null) {
            return 0;
        }
        
        count[node.val]++;
        
        if (node.left == null && node.right == null) {
            int oddCount = 0;
            for (int c : count) {
                if (c % 2 == 1) {
                    oddCount++;
                }
            }
            count[node.val]--;
            return oddCount <= 1 ? 1 : 0;
        }
        
        int result = dfs(node.left, count) + dfs(node.right, count);
        count[node.val]--;
        return result;
    }
    
    public int pseudoPalindromicPaths (TreeNode root) {
        return dfs(root, new int[10]);
    }
}

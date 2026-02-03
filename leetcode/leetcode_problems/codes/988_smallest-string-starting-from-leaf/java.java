/**
 * Problem: Smallest String Starting From Leaf
 * Difficulty: Medium
 * Tags: string, tree, graph, search
 * 
 * Approach: DFS - collect all root-to-leaf strings, return lexicographically smallest
 * Time Complexity: O(n * h) where h is height
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
    private String result = null;
    
    public String smallestFromLeaf(TreeNode root) {
        dfs(root, new StringBuilder());
        return result;
    }
    
    private void dfs(TreeNode node, StringBuilder path) {
        if (node == null) {
            return;
        }
        
        path.append((char)('a' + node.val));
        
        if (node.left == null && node.right == null) {
            String s = new StringBuilder(path).reverse().toString();
            if (result == null || s.compareTo(result) < 0) {
                result = s;
            }
        } else {
            dfs(node.left, path);
            dfs(node.right, path);
        }
        
        path.setLength(path.length() - 1);
    }
}

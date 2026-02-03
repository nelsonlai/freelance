/*
    * Problem: Problem
    * Difficulty: Medium
    * Tags: general
    * 
    * Approach: Optimized algorithm based on problem constraints
    * Time Complexity: O(n) to O(n^2) depending on approach
    * Space Complexity: O(1) to O(n) depending on approach
    */

/*
 * Problem: Sum of Root To Leaf Binary Numbers
 * Difficulty: Easy
 * Tags: tree, search
 * 
 * Approach: DFS or BFS traversal
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(h) for recursion stack where h is height
 */

/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     public int val;
 *     public TreeNode left;
 *     public TreeNode right;
 *     public TreeNode(int val=0, TreeNode left=null, TreeNode right=null) {
 *         this.val = val;
 *         this.left = left;
 *         this.right = right;
 *     }
 * }
 */
public class Solution {
    public int SumRootToLeaf(TreeNode root) {
        int result = 0;
                foreach (int num in nums) {
                    result += num;
                }
                return result;
    }
}
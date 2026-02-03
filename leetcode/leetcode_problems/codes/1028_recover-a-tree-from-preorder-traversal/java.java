/**
 * Problem: Recover a Tree From Preorder Traversal
 * Difficulty: Hard
 * Tags: string, tree, search
 * 
 * Approach: Parse string to extract depth and value, use stack to build tree
 * Time Complexity: O(n) where n is string length
 * Space Complexity: O(h) for stack where h is height
 */

import java.util.*;

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
    public TreeNode recoverFromPreorder(String traversal) {
        List<TreeNode> stack = new ArrayList<>();
        int i = 0;
        
        while (i < traversal.length()) {
            int depth = 0;
            while (i < traversal.length() && traversal.charAt(i) == '-') {
                depth++;
                i++;
            }
            
            StringBuilder numStr = new StringBuilder();
            while (i < traversal.length() && Character.isDigit(traversal.charAt(i))) {
                numStr.append(traversal.charAt(i));
                i++;
            }
            int val = Integer.parseInt(numStr.toString());
            
            TreeNode node = new TreeNode(val);
            
            while (stack.size() > depth) {
                stack.remove(stack.size() - 1);
            }
            
            if (!stack.isEmpty()) {
                if (stack.get(stack.size() - 1).left == null) {
                    stack.get(stack.size() - 1).left = node;
                } else {
                    stack.get(stack.size() - 1).right = node;
                }
            }
            
            stack.add(node);
        }
        
        return stack.isEmpty() ? null : stack.get(0);
    }
}
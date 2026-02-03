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
    public TreeNode str2tree(String s) {
        if (s == null || s.isEmpty()) {
            return null;
        }
        
        int i = 0;
        while (i < s.length() && (Character.isDigit(s.charAt(i)) || s.charAt(i) == '-')) {
            i++;
        }
        
        int val = Integer.parseInt(s.substring(0, i));
        TreeNode root = new TreeNode(val);
        
        if (i < s.length() && s.charAt(i) == '(') {
            i++;
            int start = i;
            int count = 1;
            while (i < s.length() && count > 0) {
                if (s.charAt(i) == '(') {
                    count++;
                } else if (s.charAt(i) == ')') {
                    count--;
                }
                i++;
            }
            root.left = str2tree(s.substring(start, i - 1));
        }
        
        if (i < s.length() && s.charAt(i) == '(') {
            i++;
            int start = i;
            int count = 1;
            while (i < s.length() && count > 0) {
                if (s.charAt(i) == '(') {
                    count++;
                } else if (s.charAt(i) == ')') {
                    count--;
                }
                i++;
            }
            root.right = str2tree(s.substring(start, i - 1));
        }
        
        return root;
    }
}

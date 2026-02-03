/**
 * Problem: Linked List in Binary Tree
 * Difficulty: Medium
 * Tags: tree, search, linked_list
 * 
 * Approach: DFS - try matching from each node, recursively match linked list
 * Time Complexity: O(n * m) where n is tree nodes, m is list length
 * Space Complexity: O(h) for recursion stack
 */

/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode() {}
 *     ListNode(int val) { this.val = val; }
 *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
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
    private boolean match(TreeNode node, ListNode listNode) {
        if (listNode == null) {
            return true;
        }
        if (node == null || node.val != listNode.val) {
            return false;
        }
        return match(node.left, listNode.next) || match(node.right, listNode.next);
    }
    
    public boolean isSubPath(ListNode head, TreeNode root) {
        if (root == null) {
            return false;
        }
        
        if (match(root, head)) {
            return true;
        }
        
        return isSubPath(head, root.left) || isSubPath(head, root.right);
    }
}

/**
 * Problem: Plus One Linked List
 * Difficulty: Medium
 * Tags: math, linked_list
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode() {
        // TODO: Implement optimized solution
        return 0;
    }
 *     ListNode(int val) { this.val = val; }
 *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */
class Solution {
    public ListNode plusOne(ListNode head) {
        head = reverse(head);
        ListNode node = head;
        int carry = 1;
        ListNode prev = null;
        
        while (node != null) {
            node.val += carry;
            carry = node.val / 10;
            node.val %= 10;
            prev = node;
            node = node.next;
        }
        
        if (carry > 0) {
            prev.next = new ListNode(carry);
        }
        
        return reverse(head);
    }
    
    private ListNode reverse(ListNode head) {
        ListNode prev = null;
        while (head != null) {
            ListNode next = head.next;
            head.next = prev;
            prev = head;
            head = next;
        }
        return prev;
    }
}
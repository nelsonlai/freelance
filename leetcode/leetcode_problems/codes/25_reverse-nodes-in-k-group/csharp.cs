/*
 * Problem: Reverse Nodes in k-Group
 * Difficulty: Hard
 * Tags: linked_list
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     public int val;
 *     public ListNode next;
 *     public ListNode(int val=0, ListNode next=null) {
 *         this.val = val;
 *         this.next = next;
 *     }
 * }
 */
public class Solution {
    public ListNode ReverseKGroup(ListNode head, int k) {
        ListNode current = head;
        int count = 0;
        
        while (current != null && count < k) {
            current = current.next;
            count++;
        }
        
        if (count == k) {
            current = ReverseKGroup(current, k);
            
            while (count > 0) {
                ListNode next = head.next;
                head.next = current;
                current = head;
                head = next;
                count--;
            }
            head = current;
        }
        
        return head;
    }
}
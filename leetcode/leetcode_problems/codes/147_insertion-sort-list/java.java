/**
 * Problem: Insertion Sort List
 * Difficulty: Medium
 * Tags: graph, sort, linked_list
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
    public ListNode insertionSortList(ListNode head) {
        ListNode dummy = new ListNode(0);
        dummy.next = head;
        ListNode current = head;
        
        while (current != null && current.next != null) {
            if (current.val <= current.next.val) {
                current = current.next;
            } else {
                ListNode prev = dummy;
                while (prev.next.val < current.next.val) {
                    prev = prev.next;
                }
                
                ListNode temp = current.next;
                current.next = temp.next;
                temp.next = prev.next;
                prev.next = temp;
            }
        }
        
        return dummy.next;
    }
}
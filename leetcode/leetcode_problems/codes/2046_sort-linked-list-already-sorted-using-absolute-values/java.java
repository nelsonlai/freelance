/**
 * Problem: Sort Linked List Already Sorted Using Absolute Values
 * Difficulty: Medium
 * Tags: array, sort, linked_list
 * 
 * Approach: Separate negative and positive nodes, then merge
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(1)
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
class Solution {
    public ListNode sortLinkedList(ListNode head) {
        if (head == null) {
            return head;
        }
        
        // Separate negative (reverse order) and positive nodes
        ListNode negHead = null;
        ListNode posHead = null;
        ListNode negTail = null;
        ListNode posTail = null;
        
        ListNode curr = head;
        while (curr != null) {
            ListNode next = curr.next;
            curr.next = null;
            
            if (curr.val < 0) {
                // Add to negative list (in reverse order)
                if (negHead == null) {
                    negHead = curr;
                    negTail = curr;
                } else {
                    curr.next = negHead;
                    negHead = curr;
                }
            } else {
                // Add to positive list (in order)
                if (posHead == null) {
                    posHead = curr;
                    posTail = curr;
                } else {
                    posTail.next = curr;
                    posTail = curr;
                }
            }
            
            curr = next;
        }
        
        // Merge negative and positive lists
        if (negHead != null) {
            if (posHead != null) {
                negTail.next = posHead;
            }
            return negHead;
        } else {
            return posHead;
        }
    }
}

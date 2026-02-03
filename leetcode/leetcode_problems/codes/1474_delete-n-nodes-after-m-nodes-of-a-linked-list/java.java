/**
 * Problem: Delete N Nodes After M Nodes of a Linked List
 * Difficulty: Easy
 * Tags: linked_list
 * 
 * Approach: Traverse, keep m nodes, skip n nodes, repeat
 * Time Complexity: O(len(head))
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
    public ListNode deleteNodes(ListNode head, int m, int n) {
        ListNode current = head;
        
        while (current != null) {
            for (int i = 0; i < m - 1 && current != null; i++) {
                current = current.next;
            }
            
            if (current == null) {
                break;
            }
            
            ListNode temp = current.next;
            for (int i = 0; i < n && temp != null; i++) {
                temp = temp.next;
            }
            
            current.next = temp;
            current = temp;
        }
        
        return head;
    }
}

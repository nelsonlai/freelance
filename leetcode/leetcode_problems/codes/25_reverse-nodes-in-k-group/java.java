/**
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
    public ListNode reverseKGroup(ListNode head, int k) {
        ListNode current = head;
        int count = 0;
        
        while (current != null && count < k) {
            current = current.next;
            count++;
        }
        
        if (count == k) {
            current = reverseKGroup(current, k);
            
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
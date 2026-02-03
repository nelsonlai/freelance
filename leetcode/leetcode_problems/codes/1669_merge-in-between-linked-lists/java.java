/**
 * Problem: Merge In Between Linked Lists
 * Difficulty: Medium
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
 *     ListNode() {}
 *     ListNode(int val) { this.val = val; }
 *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */
class Solution {
    public ListNode mergeInBetween(ListNode list1, int a, int b, ListNode list2) {
        ListNode prev = null;
        ListNode curr = list1;
        
        // Find node at position a-1
        for (int i = 0; i < a; i++) {
            prev = curr;
            curr = curr.next;
        }
        
        // Connect prev to list2
        prev.next = list2;
        
        // Find node at position b+1
        for (int i = 0; i < b - a + 1; i++) {
            curr = curr.next;
        }
        
        // Find end of list2 and connect to curr
        ListNode end = list2;
        while (end.next != null) {
            end = end.next;
        }
        end.next = curr;
        
        return list1;
    }
}
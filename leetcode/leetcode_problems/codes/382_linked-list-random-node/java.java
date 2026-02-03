/**
 * Problem: Linked List Random Node
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
import java.util.*;

class Solution {
    private ListNode head;

    public Solution(ListNode head) {
        this.head = head;
    }
    
    public int getRandom() {
        int result = 0;
        int count = 0;
        ListNode current = head;
        
        while (current != null) {
            count++;
            if (Math.random() < 1.0 / count) {
                result = current.val;
            }
            current = current.next;
        }
        
        return result;
    }
}

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(head);
 * int param_1 = obj.getRandom();
 */
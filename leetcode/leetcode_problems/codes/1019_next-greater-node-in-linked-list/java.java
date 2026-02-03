/**
 * Problem: Next Greater Node In Linked List
 * Difficulty: Medium
 * Tags: array, linked_list, stack
 * 
 * Approach: Convert to array, use monotonic stack to find next greater element
 * Time Complexity: O(n)
 * Space Complexity: O(n) for stack and array
 */

import java.util.*;

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
    public int[] nextLargerNodes(ListNode head) {
        List<Integer> arr = new ArrayList<>();
        while (head != null) {
            arr.add(head.val);
            head = head.next;
        }
        
        int[] result = new int[arr.size()];
        Stack<Integer> stack = new Stack<>();
        
        for (int i = 0; i < arr.size(); i++) {
            while (!stack.isEmpty() && arr.get(stack.peek()) < arr.get(i)) {
                result[stack.pop()] = arr.get(i);
            }
            stack.push(i);
        }
        
        return result;
    }
}
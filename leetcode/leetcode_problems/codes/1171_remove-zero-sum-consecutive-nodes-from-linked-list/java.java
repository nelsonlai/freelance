/**
 * Problem: Remove Zero Sum Consecutive Nodes from Linked List
 * Difficulty: Medium
 * Tags: hash, linked_list
 * 
 * Approach: Use prefix sum with hash map - if same prefix sum appears, remove nodes in between
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(n) for hash map
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
import java.util.HashMap;

class Solution {
    public ListNode removeZeroSumSublists(ListNode head) {
        ListNode dummy = new ListNode(0);
        dummy.next = head;
        HashMap<Integer, ListNode> prefixMap = new HashMap<>();
        prefixMap.put(0, dummy);
        
        int prefixSum = 0;
        ListNode current = head;
        
        while (current != null) {
            prefixSum += current.val;
            if (prefixMap.containsKey(prefixSum)) {
                ListNode prev = prefixMap.get(prefixSum);
                ListNode temp = prev.next;
                int tempSum = prefixSum;
                
                while (temp != current) {
                    tempSum += temp.val;
                    if (tempSum != prefixSum) {
                        prefixMap.remove(tempSum);
                    }
                    temp = temp.next;
                }
                
                prev.next = current.next;
            } else {
                prefixMap.put(prefixSum, current);
            }
            current = current.next;
        }
        
        return dummy.next;
    }
}

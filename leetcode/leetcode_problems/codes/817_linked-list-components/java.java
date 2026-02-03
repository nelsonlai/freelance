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
    public int numComponents(ListNode head, int[] nums) {
        Set<Integer> numSet = new HashSet<>();
        for (int num : nums) {
            numSet.add(num);
        }
        
        int result = 0;
        boolean inComponent = false;
        
        while (head != null) {
            if (numSet.contains(head.val)) {
                if (!inComponent) {
                    result++;
                    inComponent = true;
                }
            } else {
                inComponent = false;
            }
            head = head.next;
        }
        
        return result;
    }
}

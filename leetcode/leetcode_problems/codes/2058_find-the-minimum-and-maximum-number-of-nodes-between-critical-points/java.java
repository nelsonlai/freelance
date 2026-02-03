/**
 * Problem: Find the Minimum and Maximum Number of Nodes Between Critical Points
 * Difficulty: Medium
 * Tags: array, linked_list
 * 
 * Approach: Traverse linked list, find critical points, calculate min and max distances
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
    public int[] nodesBetweenCriticalPoints(ListNode head) {
        if (head == null || head.next == null || head.next.next == null) {
            return new int[]{-1, -1};
        }
        
        List<Integer> criticalPoints = new ArrayList<>();
        ListNode prev = head;
        ListNode curr = head.next;
        int index = 1;
        
        while (curr.next != null) {
            // Check if current is a critical point
            if ((prev.val < curr.val && curr.val > curr.next.val) ||
                (prev.val > curr.val && curr.val < curr.next.val)) {
                criticalPoints.add(index);
            }
            
            prev = curr;
            curr = curr.next;
            index++;
        }
        
        if (criticalPoints.size() < 2) {
            return new int[]{-1, -1};
        }
        
        // Minimum distance is between consecutive critical points
        int minDist = Integer.MAX_VALUE;
        for (int i = 1; i < criticalPoints.size(); i++) {
            minDist = Math.min(minDist, criticalPoints.get(i) - criticalPoints.get(i - 1));
        }
        
        // Maximum distance is between first and last
        int maxDist = criticalPoints.get(criticalPoints.size() - 1) - criticalPoints.get(0);
        
        return new int[]{minDist, maxDist};
    }
}
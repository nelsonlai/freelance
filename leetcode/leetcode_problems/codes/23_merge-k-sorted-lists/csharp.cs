/*
 * Problem: Merge k Sorted Lists
 * Difficulty: Hard
 * Tags: array, sort, linked_list, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     public int val;
 *     public ListNode next;
 *     public ListNode(int val=0, ListNode next=null) {
 *         this.val = val;
 *         this.next = next;
 *     }
 * }
 */
using System.Collections.Generic;

public class Solution {
    public ListNode MergeKLists(ListNode[] lists) {
        if (lists == null || lists.Length == 0) {
            return null;
        }
        
        var heap = new SortedSet<(int val, int idx, ListNode node)>(Comparer<(int, int, ListNode)>.Create((a, b) => {
            if (a.val != b.val) return a.val.CompareTo(b.val);
            return a.idx.CompareTo(b.idx);
        }));
        
        for (int i = 0; i < lists.Length; i++) {
            if (lists[i] != null) {
                heap.Add((lists[i].val, i, lists[i]));
            }
        }
        
        ListNode dummy = new ListNode(0);
        ListNode current = dummy;
        
        while (heap.Count > 0) {
            var min = heap.Min;
            heap.Remove(min);
            current.next = min.node;
            current = current.next;
            
            if (min.node.next != null) {
                heap.Add((min.node.next.val, min.idx, min.node.next));
            }
        }
        
        return dummy.next;
    }
}
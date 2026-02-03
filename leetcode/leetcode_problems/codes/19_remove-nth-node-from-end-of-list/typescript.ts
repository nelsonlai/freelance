/**
 * Problem: Remove Nth Node From End of List
 * Difficulty: Medium
 * Tags: array, linked_list
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

/**
 * Definition for singly-linked list.
 * class ListNode {
 *     val: number
 *     next: ListNode | null
 *     constructor(val?: number, next?: ListNode | null) {
 *         this.val = (val===undefined ? 0 : val)
 *         this.next = (next===undefined ? null : next)
 *     }
 * }
 */

function removeNthFromEnd(head: ListNode | null, n: number): ListNode | null {
    const dummy = new ListNode(0);
    dummy.next = head;
    let first: ListNode | null = dummy;
    let second: ListNode | null = dummy;
    
    for (let i = 0; i <= n; i++) {
        first = first!.next;
    }
    
    while (first !== null) {
        first = first.next;
        second = second!.next;
    }
    
    second!.next = second!.next!.next;
    return dummy.next;
};
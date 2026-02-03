/**
 * Problem: Swap Nodes in Pairs
 * Difficulty: Medium
 * Tags: linked_list
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
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

function swapPairs(head: ListNode | null): ListNode | null {
    const dummy = new ListNode(0);
    dummy.next = head;
    let prev: ListNode | null = dummy;
    
    while (prev!.next !== null && prev!.next.next !== null) {
        const first = prev!.next;
        const second = prev!.next.next;
        
        prev!.next = second;
        first!.next = second!.next;
        second!.next = first;
        
        prev = first;
    }
    
    return dummy.next;
};
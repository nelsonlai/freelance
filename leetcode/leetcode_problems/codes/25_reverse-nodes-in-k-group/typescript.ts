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
 * class ListNode {
 *     val: number
 *     next: ListNode | null
 *     constructor(val?: number, next?: ListNode | null) {
 *         this.val = (val===undefined ? 0 : val)
 *         this.next = (next===undefined ? null : next)
 *     }
 * }
 */

function reverseKGroup(head: ListNode | null, k: number): ListNode | null {
    let current: ListNode | null = head;
    let count = 0;
    
    while (current !== null && count < k) {
        current = current.next;
        count++;
    }
    
    if (count === k) {
        current = reverseKGroup(current, k);
        
        while (count > 0) {
            const next = head!.next;
            head!.next = current;
            current = head;
            head = next;
            count--;
        }
        head = current;
    }
    
    return head;
};
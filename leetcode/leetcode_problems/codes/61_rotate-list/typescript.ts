/**
 * Problem: Rotate List
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

function rotateRight(head: ListNode | null, k: number): ListNode | null {
    if (!head || !head.next || k === 0) {
        return head;
    }
    
    // Find length and get tail
    let length = 1;
    let tail = head;
    while (tail.next) {
        tail = tail.next;
        length++;
    }
    
    k = k % length;
    if (k === 0) {
        return head;
    }
    
    // Find new tail
    let newTail = head;
    for (let i = 0; i < length - k - 1; i++) {
        newTail = newTail.next;
    }
    
    // Rotate
    let newHead = newTail.next;
    newTail.next = null;
    tail.next = head;
    
    return newHead;
};
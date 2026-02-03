/**
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
 * class ListNode {
 *     val: number
 *     next: ListNode | null
 *     constructor(val?: number, next?: ListNode | null) {
 *         this.val = (val===undefined ? 0 : val)
 *         this.next = (next===undefined ? null : next)
 *     }
 * }
 */

function mergeKLists(lists: Array<ListNode | null>): ListNode | null {
    if (!lists || lists.length === 0) {
        return null;
    }
    
    while (lists.length > 1) {
        const merged: (ListNode | null)[] = [];
        for (let i = 0; i < lists.length; i += 2) {
            const l1 = lists[i];
            const l2 = (i + 1 < lists.length) ? lists[i + 1] : null;
            merged.push(mergeTwo(l1, l2));
        }
        lists = merged;
    }
    
    return lists[0];
}

function mergeTwo(l1: ListNode | null, l2: ListNode | null): ListNode | null {
    const dummy = new ListNode(0);
    let current: ListNode | null = dummy;
    
    while (l1 !== null && l2 !== null) {
        if (l1.val <= l2.val) {
            current!.next = l1;
            l1 = l1.next;
        } else {
            current!.next = l2;
            l2 = l2.next;
        }
        current = current!.next;
    }
    
    current!.next = l1 !== null ? l1 : l2;
    return dummy.next;
};
// Problem: Rotate List
// Difficulty: Medium
// Tags: array, linked_list
// 
// Approach: Use two pointers or sliding window technique
// Time Complexity: O(n) or O(n log n)
// Space Complexity: O(1) to O(n) depending on approach

/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func rotateRight(head *ListNode, k int) *ListNode {
    if head == nil || head.Next == nil || k == 0 {
        return head
    }
    
    // Find length and get tail
    length := 1
    tail := head
    for tail.Next != nil {
        tail = tail.Next
        length++
    }
    
    k = k % length
    if k == 0 {
        return head
    }
    
    // Find new tail
    newTail := head
    for i := 0; i < length-k-1; i++ {
        newTail = newTail.Next
    }
    
    // Rotate
    newHead := newTail.Next
    newTail.Next = nil
    tail.Next = head
    
    return newHead
}
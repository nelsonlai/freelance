// Problem: Remove Nth Node From End of List
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
func removeNthFromEnd(head *ListNode, n int) *ListNode {
    dummy := &ListNode{Val: 0, Next: head}
    first := dummy
    second := dummy
    
    for i := 0; i <= n; i++ {
        first = first.Next
    }
    
    for first != nil {
        first = first.Next
        second = second.Next
    }
    
    second.Next = second.Next.Next
    return dummy.Next
}
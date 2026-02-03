// Problem: Swap Nodes in Pairs
// Difficulty: Medium
// Tags: linked_list
// 
// Approach: Optimized algorithm based on problem constraints
// Time Complexity: O(n) to O(n^2) depending on approach
// Space Complexity: O(1) to O(n) depending on approach

/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
func swapPairs(head *ListNode) *ListNode {
    dummy := &ListNode{Val: 0}
    dummy.Next = head
    prev := dummy
    
    for prev.Next != nil && prev.Next.Next != nil {
        first := prev.Next
        second := prev.Next.Next
        
        prev.Next = second
        first.Next = second.Next
        second.Next = first
        
        prev = first
    }
    
    return dummy.Next
}
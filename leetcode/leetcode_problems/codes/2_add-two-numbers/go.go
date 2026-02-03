// Problem: Add Two Numbers
// Difficulty: Medium
// Tags: math, linked_list
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
func addTwoNumbers(l1 *ListNode, l2 *ListNode) *ListNode {
    dummy := &ListNode{Val: 0}
    current := dummy
    carry := 0
    
    for l1 != nil || l2 != nil || carry != 0 {
        val1 := 0
        if l1 != nil {
            val1 = l1.Val
        }
        val2 := 0
        if l2 != nil {
            val2 = l2.Val
        }
        sum := val1 + val2 + carry
        carry = sum / 10
        current.Next = &ListNode{Val: sum % 10}
        current = current.Next
        if l1 != nil {
            l1 = l1.Next
        }
        if l2 != nil {
            l2 = l2.Next
        }
    }
    
    return dummy.Next
}
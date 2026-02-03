// Problem: Reverse Nodes in k-Group
// Difficulty: Hard
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
func reverseKGroup(head *ListNode, k int) *ListNode {
    current := head
    count := 0
    
    for current != nil && count < k {
        current = current.Next
        count++
    }
    
    if count == k {
        current = reverseKGroup(current, k)
        
        for count > 0 {
            next := head.Next
            head.Next = current
            current = head
            head = next
            count--
        }
        head = current
    }
    
    return head
}
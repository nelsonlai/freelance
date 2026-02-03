// Problem: Merge k Sorted Lists
// Difficulty: Hard
// Tags: array, sort, linked_list, queue, heap
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
func mergeKLists(lists []*ListNode) *ListNode {
    if len(lists) == 0 {
        return nil
    }
    
    for len(lists) > 1 {
        merged := []*ListNode{}
        for i := 0; i < len(lists); i += 2 {
            var l2 *ListNode
            if i+1 < len(lists) {
                l2 = lists[i+1]
            }
            merged = append(merged, mergeTwo(lists[i], l2))
        }
        lists = merged
    }
    
    return lists[0]
}

func mergeTwo(l1, l2 *ListNode) *ListNode {
    dummy := &ListNode{Val: 0}
    current := dummy
    
    for l1 != nil && l2 != nil {
        if l1.Val <= l2.Val {
            current.Next = l1
            l1 = l1.Next
        } else {
            current.Next = l2
            l2 = l2.Next
        }
        current = current.Next
    }
    
    if l1 != nil {
        current.Next = l1
    } else {
        current.Next = l2
    }
    
    return dummy.Next
}
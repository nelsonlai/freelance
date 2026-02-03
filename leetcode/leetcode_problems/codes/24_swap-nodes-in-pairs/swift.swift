/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     public var val: Int
 *     public var next: ListNode?
 *     public init() { self.val = 0; self.next = nil; }
 *     public init(_ val: Int) { self.val = val; self.next = nil; }
 *     public init(_ val: Int, _ next: ListNode?) { self.val = val; self.next = next; }
 * }
 */
class Solution {
    func swapPairs(_ head: ListNode?) -> ListNode? {
        let dummy = ListNode(0)
        dummy.next = head
        var prev: ListNode? = dummy
        
        while prev?.next != nil && prev?.next?.next != nil {
            let first = prev?.next
            let second = prev?.next?.next
            
            prev?.next = second
            first?.next = second?.next
            second?.next = first
            
            prev = first
        }
        
        return dummy.next
    }
}
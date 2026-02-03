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
    func rotateRight(_ head: ListNode?, _ k: Int) -> ListNode? {
        guard let head = head, head.next != nil, k != 0 else {
            return head
        }
        
        // Find length and get tail
        var length = 1
        var tail = head
        while let next = tail.next {
            tail = next
            length += 1
        }
        
        let k = k % length
        if k == 0 {
            return head
        }
        
        // Find new tail
        var newTail = head
        for _ in 0..<(length - k - 1) {
            newTail = newTail.next!
        }
        
        // Rotate
        let newHead = newTail.next
        newTail.next = nil
        tail.next = head
        
        return newHead
    }
}
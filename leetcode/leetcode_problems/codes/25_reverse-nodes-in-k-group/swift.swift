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
    func reverseKGroup(_ head: ListNode?, _ k: Int) -> ListNode? {
        var current = head
        var count = 0
        
        while current != nil && count < k {
            current = current?.next
            count += 1
        }
        
        if count == k {
            current = reverseKGroup(current, k)
            var head = head
            var current = current
            
            while count > 0 {
                let next = head?.next
                head?.next = current
                current = head
                head = next
                count -= 1
            }
            return current
        }
        
        return head
    }
}
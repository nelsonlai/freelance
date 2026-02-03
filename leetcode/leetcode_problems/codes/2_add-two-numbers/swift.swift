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
    func addTwoNumbers(_ l1: ListNode?, _ l2: ListNode?) -> ListNode? {
        let dummy = ListNode(0)
        var current = dummy
        var carry = 0
        var p1 = l1
        var p2 = l2
        
        while p1 != nil || p2 != nil || carry != 0 {
            let val1 = p1?.val ?? 0
            let val2 = p2?.val ?? 0
            let sum = val1 + val2 + carry
            carry = sum / 10
            current.next = ListNode(sum % 10)
            current = current.next!
            p1 = p1?.next
            p2 = p2?.next
        }
        
        return dummy.next
    }
}
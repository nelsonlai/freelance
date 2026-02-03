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
    func mergeKLists(_ lists: [ListNode?]) -> ListNode? {
        if lists.isEmpty {
            return nil
        }
        
        var lists = lists
        while lists.count > 1 {
            var merged: [ListNode?] = []
            for i in stride(from: 0, to: lists.count, by: 2) {
                let l1 = lists[i]
                let l2 = (i + 1 < lists.count) ? lists[i + 1] : nil
                merged.append(mergeTwo(l1, l2))
            }
            lists = merged
        }
        
        return lists[0]
    }
    
    func mergeTwo(_ l1: ListNode?, _ l2: ListNode?) -> ListNode? {
        let dummy = ListNode(0)
        var current: ListNode? = dummy
        var l1 = l1
        var l2 = l2
        
        while l1 != nil && l2 != nil {
            if l1!.val <= l2!.val {
                current?.next = l1
                l1 = l1?.next
            } else {
                current?.next = l2
                l2 = l2?.next
            }
            current = current?.next
        }
        
        current?.next = l1 ?? l2
        return dummy.next
    }
}
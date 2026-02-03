/**
 * Definition for singly-linked list.
 * class ListNode(_x: Int = 0, _next: ListNode = null) {
 *   var next: ListNode = _next
 *   var x: Int = _x
 * }
 */
object Solution {
    def reverseKGroup(head: ListNode, k: Int): ListNode = {
        var current = head
        var count = 0
        
        while (current != null && count < k) {
            current = current.next
            count += 1
        }
        
        if (count == k) {
            current = reverseKGroup(current, k)
            var head = head
            var current = current
            
            while (count > 0) {
                val next = head.next
                head.next = current
                current = head
                head = next
                count -= 1
            }
            return current
        }
        
        head
    }
}
/**
 * Definition for singly-linked list.
 * class ListNode(_x: Int = 0, _next: ListNode = null) {
 *   var next: ListNode = _next
 *   var x: Int = _x
 * }
 */
object Solution {
    def swapPairs(head: ListNode): ListNode = {
        val dummy = new ListNode(0)
        dummy.next = head
        var prev = dummy
        
        while (prev.next != null && prev.next.next != null) {
            val first = prev.next
            val second = prev.next.next
            
            prev.next = second
            first.next = second.next
            second.next = first
            
            prev = first
        }
        
        dummy.next
    }
}
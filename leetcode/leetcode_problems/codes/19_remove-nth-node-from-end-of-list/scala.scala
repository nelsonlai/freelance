/**
 * Definition for singly-linked list.
 * class ListNode(_x: Int = 0, _next: ListNode = null) {
 *   var next: ListNode = _next
 *   var x: Int = _x
 * }
 */
object Solution {
    def removeNthFromEnd(head: ListNode, n: Int): ListNode = {
        val dummy = new ListNode(0)
        dummy.next = head
        var first = dummy
        var second = dummy
        
        for (_ <- 0 to n) {
            first = first.next
        }
        
        while (first.next != null) {
            first = first.next
            second = second.next
        }
        
        second.next = second.next.next
        dummy.next
    }
}
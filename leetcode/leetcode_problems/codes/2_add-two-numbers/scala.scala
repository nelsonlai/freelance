/**
 * Definition for singly-linked list.
 * class ListNode(_x: Int = 0, _next: ListNode = null) {
 *   var next: ListNode = _next
 *   var x: Int = _x
 * }
 */
object Solution {
    def addTwoNumbers(l1: ListNode, l2: ListNode): ListNode = {
        val dummy = new ListNode(0)
        var current = dummy
        var carry = 0
        var p1 = l1
        var p2 = l2
        
        while (p1 != null || p2 != null || carry != 0) {
            val val1 = if (p1 != null) p1.x else 0
            val val2 = if (p2 != null) p2.x else 0
            val sum = val1 + val2 + carry
            carry = sum / 10
            current.next = new ListNode(sum % 10)
            current = current.next
            if (p1 != null) p1 = p1.next
            if (p2 != null) p2 = p2.next
        }
        
        dummy.next
    }
}
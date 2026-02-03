/**
 * Definition for singly-linked list.
 * class ListNode(_x: Int = 0, _next: ListNode = null) {
 *   var next: ListNode = _next
 *   var x: Int = _x
 * }
 */
object Solution {
    def rotateRight(head: ListNode, k: Int): ListNode = {
        if (head == null || head.next == null || k == 0) {
            return head
        }
        
        // Find length and get tail
        var length = 1
        var tail = head
        while (tail.next != null) {
            tail = tail.next
            length += 1
        }
        
        val k = k % length
        if (k == 0) {
            return head
        }
        
        // Find new tail
        var newTail = head
        for (i <- 0 until length - k - 1) {
            newTail = newTail.next
        }
        
        // Rotate
        val newHead = newTail.next
        newTail.next = null
        tail.next = head
        
        newHead
    }
}
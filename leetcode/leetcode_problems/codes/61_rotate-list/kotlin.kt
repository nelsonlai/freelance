/**
 * Example:
 * var li = ListNode(5)
 * var v = li.`val`
 * Definition for singly-linked list.
 * class ListNode(var `val`: Int) {
 *     var next: ListNode? = null
 * }
 */
class Solution {
    fun rotateRight(head: ListNode?, k: Int): ListNode? {
        if (head == null || head.next == null || k == 0) {
            return head
        }
        
        // Find length and get tail
        var length = 1
        var tail = head
        while (tail?.next != null) {
            tail = tail.next
            length++
        }
        
        val k = k % length
        if (k == 0) {
            return head
        }
        
        // Find new tail
        var newTail = head
        for (i in 0 until length - k - 1) {
            newTail = newTail?.next
        }
        
        // Rotate
        val newHead = newTail?.next
        newTail?.next = null
        tail?.next = head
        
        return newHead
    }
}
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
    fun swapPairs(head: ListNode?): ListNode? {
        val dummy = ListNode(0)
        dummy.next = head
        var prev: ListNode? = dummy
        
        while (prev?.next != null && prev?.next?.next != null) {
            val first = prev?.next
            val second = prev?.next?.next
            
            prev?.next = second
            first?.next = second?.next
            second?.next = first
            
            prev = first
        }
        
        return dummy.next
    }
}
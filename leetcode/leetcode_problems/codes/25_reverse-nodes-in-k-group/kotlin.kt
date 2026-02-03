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
    fun reverseKGroup(head: ListNode?, k: Int): ListNode? {
        var current = head
        var count = 0
        
        while (current != null && count < k) {
            current = current.next
            count++
        }
        
        if (count == k) {
            current = reverseKGroup(current, k)
            var head = head
            var current = current
            
            while (count > 0) {
                val next = head?.next
                head?.next = current
                current = head
                head = next
                count--
            }
            return current
        }
        
        return head
    }
}
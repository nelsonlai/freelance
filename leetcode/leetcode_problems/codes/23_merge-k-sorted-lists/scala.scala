/**
 * Definition for singly-linked list.
 * class ListNode(_x: Int = 0, _next: ListNode = null) {
 *   var next: ListNode = _next
 *   var x: Int = _x
 * }
 */
object Solution {
    def mergeKLists(lists: Array[ListNode]): ListNode = {
        if (lists.isEmpty) {
            return null
        }
        
        var lists = lists.toList
        while (lists.length > 1) {
            val merged = (0 until lists.length by 2).map { i =>
                val l1 = lists(i)
                val l2 = if (i + 1 < lists.length) lists(i + 1) else null
                mergeTwo(l1, l2)
            }
            lists = merged
        }
        
        lists.head
    }
    
    def mergeTwo(l1: ListNode, l2: ListNode): ListNode = {
        val dummy = new ListNode(0)
        var current = dummy
        var l1 = l1
        var l2 = l2
        
        while (l1 != null && l2 != null) {
            if (l1.x <= l2.x) {
                current.next = l1
                l1 = l1.next
            } else {
                current.next = l2
                l2 = l2.next
            }
            current = current.next
        }
        
        current.next = if (l1 != null) l1 else l2
        dummy.next
    }
}
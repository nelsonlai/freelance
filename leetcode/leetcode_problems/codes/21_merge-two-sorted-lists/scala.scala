/**
 * Definition for singly-linked list.
 * class ListNode(_x: Int = 0, _next: ListNode = null) {
 *   var next: ListNode = _next
 *   var x: Int = _x
 * }
 */
object Solution {
    def mergeTwoLists(list1: ListNode, list2: ListNode): ListNode = {
        val dummy = new ListNode(0)
        var current = dummy
        var l1 = list1
        var l2 = list2
        
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
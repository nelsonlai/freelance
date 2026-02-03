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
    fun mergeKLists(lists: Array<ListNode?>): ListNode? {
        if (lists.isEmpty()) {
            return null
        }
        
        var lists = lists.toMutableList()
        while (lists.size > 1) {
            val merged = mutableListOf<ListNode?>()
            for (i in lists.indices step 2) {
                val l1 = lists[i]
                val l2 = if (i + 1 < lists.size) lists[i + 1] else null
                merged.add(mergeTwo(l1, l2))
            }
            lists = merged
        }
        
        return lists[0]
    }
    
    private fun mergeTwo(l1: ListNode?, l2: ListNode?): ListNode? {
        val dummy = ListNode(0)
        var current: ListNode? = dummy
        var l1 = l1
        var l2 = l2
        
        while (l1 != null && l2 != null) {
            if (l1.`val` <= l2.`val`) {
                current?.next = l1
                l1 = l1.next
            } else {
                current?.next = l2
                l2 = l2.next
            }
            current = current?.next
        }
        
        current?.next = l1 ?: l2
        return dummy.next
    }
}
# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution(object):
    def reverseKGroup(self, head, k):
        """
        :type head: Optional[ListNode]
        :type k: int
        :rtype: Optional[ListNode]
        """
        count = 0
        current = head
        while current and count < k:
            current = current.next
            count += 1
        
        if count == k:
            current = self.reverseKGroup(current, k)
            while count > 0:
                next_node = head.next
                head.next = current
                current = head
                head = next_node
                count -= 1
            head = current
        
        return head
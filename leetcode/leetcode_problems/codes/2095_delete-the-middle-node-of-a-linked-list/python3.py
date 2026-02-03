"""
Problem: Delete the Middle Node of a Linked List
Difficulty: Medium
Tags: array, linked_list, two pointers

Approach: Use slow and fast pointers to find middle node
Time Complexity: O(n) where n is number of nodes
Space Complexity: O(1)
"""

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def deleteMiddle(self, head: Optional[ListNode]) -> Optional[ListNode]:
        if not head or not head.next:
            return None
        
        slow = head
        fast = head
        prev = None
        
        while fast and fast.next:
            prev = slow
            slow = slow.next
            fast = fast.next.next
        
        # Delete slow (middle node)
        prev.next = slow.next
        
        return head
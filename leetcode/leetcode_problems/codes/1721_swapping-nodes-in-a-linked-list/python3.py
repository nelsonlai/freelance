"""
Problem: Swapping Nodes in a Linked List
Difficulty: Medium
Tags: array, linked_list, two pointers

Approach: Find kth from start and kth from end, swap their values
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def swapNodes(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
        # Find length
        length = 0
        curr = head
        while curr:
            length += 1
            curr = curr.next
        
        # Find kth from start and kth from end
        first = head
        for _ in range(k - 1):
            first = first.next
        
        second = head
        for _ in range(length - k):
            second = second.next
        
        # Swap values
        first.val, second.val = second.val, first.val
        
        return head
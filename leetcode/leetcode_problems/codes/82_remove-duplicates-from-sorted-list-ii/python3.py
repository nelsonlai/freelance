"""
Problem: Remove Duplicates from Sorted List II
Difficulty: Medium
Tags: array, sort, linked_list

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def deleteDuplicates(self, head: Optional[ListNode]) -> Optional[ListNode]:
        dummy = ListNode(0)
        dummy.next = head
        prev = dummy
        current = head
        
        while current:
            if current.next and current.val == current.next.val:
                val = current.val
                while current and current.val == val:
                    current = current.next
                prev.next = current
            else:
                prev = current
                current = current.next
        
        return dummy.next
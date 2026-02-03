"""
Problem: Merge In Between Linked Lists
Difficulty: Medium
Tags: linked_list

Approach: Find nodes at positions a-1 and b+1, connect list2 between them
Time Complexity: O(n) where n is length of list1
Space Complexity: O(1)
"""

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def mergeInBetween(self, list1: ListNode, a: int, b: int, list2: ListNode) -> ListNode:
        prev = None
        curr = list1
        
        # Find node at position a-1
        for _ in range(a):
            prev = curr
            curr = curr.next
        
        # Connect prev to list2
        prev.next = list2
        
        # Find node at position b+1
        for _ in range(b - a + 1):
            curr = curr.next
        
        # Find end of list2 and connect to curr
        end = list2
        while end.next:
            end = end.next
        end.next = curr
        
        return list1
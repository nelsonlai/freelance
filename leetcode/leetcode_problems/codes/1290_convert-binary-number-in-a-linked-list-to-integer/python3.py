"""
Problem: Convert Binary Number in a Linked List to Integer
Difficulty: Easy
Tags: graph, math, linked_list

Approach: Traverse linked list, build binary number, convert to decimal
Time Complexity: O(n) where n is number of nodes
Space Complexity: O(1)
"""

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def getDecimalValue(self, head: Optional[ListNode]) -> int:
        result = 0
        while head:
            result = result * 2 + head.val
            head = head.next
        return result
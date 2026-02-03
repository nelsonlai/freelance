"""
Problem: Linked List Random Node
Difficulty: Medium
Tags: math, linked_list

Approach: Optimized algorithm based on problem constraints
Time Complexity: O(n) to O(n^2) depending on approach
Space Complexity: O(1) to O(n) depending on approach
"""

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
import random

class Solution:

    def __init__(self, head: Optional[ListNode]):
        self.head = head

    def getRandom(self) -> int:
        result = None
        count = 0
        current = self.head
        
        while current:
            count += 1
            if random.randint(1, count) == 1:
                result = current.val
            current = current.next
        
        return result
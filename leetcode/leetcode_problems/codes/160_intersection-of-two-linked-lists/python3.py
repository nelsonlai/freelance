"""
Problem: Intersection of Two Linked Lists
Difficulty: Easy
Tags: array, hash, linked_list

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def getIntersectionNode(self, headA: ListNode, headB: ListNode) -> Optional[ListNode]:
        if not headA or not headB:
            return None
        
        a = headA
        b = headB
        
        while a != b:
            a = a.next if a else headB
            b = b.next if b else headA
        
        return a
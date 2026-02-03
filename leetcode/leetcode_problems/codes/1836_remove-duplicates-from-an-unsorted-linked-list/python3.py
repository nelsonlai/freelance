"""
Problem: Remove Duplicates From an Unsorted Linked List
Difficulty: Medium
Tags: hash, linked_list

Approach: Count frequencies, remove nodes with count > 1
Time Complexity: O(n) where n is length
Space Complexity: O(n)
"""

from collections import Counter

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def deleteDuplicatesUnsorted(self, head: ListNode) -> ListNode:
        count = Counter()
        curr = head
        while curr:
            count[curr.val] += 1
            curr = curr.next
        
        dummy = ListNode(0)
        dummy.next = head
        prev = dummy
        curr = head
        
        while curr:
            if count[curr.val] > 1:
                prev.next = curr.next
            else:
                prev = curr
            curr = curr.next
        
        return dummy.next
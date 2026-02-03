"""
Problem: Plus One Linked List
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
class Solution:
    def plusOne(self, head: ListNode) -> ListNode:
        def reverse(node):
            prev = None
            while node:
                next_node = node.next
                node.next = prev
                prev = node
                node = next_node
            return prev
        
        head = reverse(head)
        carry = 1
        node = head
        prev = None
        
        while node:
            node.val += carry
            carry = node.val // 10
            node.val %= 10
            prev = node
            node = node.next
        
        if carry:
            prev.next = ListNode(carry)
        
        return reverse(head)
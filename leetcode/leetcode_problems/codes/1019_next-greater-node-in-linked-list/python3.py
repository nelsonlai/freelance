"""
Problem: Next Greater Node In Linked List
Difficulty: Medium
Tags: array, linked_list, stack

Approach: Convert to array, use monotonic stack to find next greater element
Time Complexity: O(n)
Space Complexity: O(n) for stack and array
"""

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def nextLargerNodes(self, head: Optional[ListNode]) -> List[int]:
        # Convert to array
        arr = []
        while head:
            arr.append(head.val)
            head = head.next
        
        result = [0] * len(arr)
        stack = []
        
        for i in range(len(arr)):
            while stack and arr[stack[-1]] < arr[i]:
                result[stack.pop()] = arr[i]
            stack.append(i)
        
        return result
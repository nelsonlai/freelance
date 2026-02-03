"""
Problem: Delete N Nodes After M Nodes of a Linked List
Difficulty: Easy
Tags: linked_list

Approach: Traverse, keep m nodes, skip n nodes, repeat
Time Complexity: O(len(head))
Space Complexity: O(1)
"""

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def deleteNodes(self, head: Optional[ListNode], m: int, n: int) -> Optional[ListNode]:
        current = head
        
        while current:
            for _ in range(m - 1):
                if current:
                    current = current.next
            
            if not current:
                break
            
            temp = current.next
            for _ in range(n):
                if temp:
                    temp = temp.next
            
            current.next = temp
            current = temp
        
        return head
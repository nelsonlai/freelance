"""
Problem: Insertion Sort List
Difficulty: Medium
Tags: graph, sort, linked_list

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
    def insertionSortList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        dummy = ListNode(0)
        dummy.next = head
        current = head
        
        while current and current.next:
            if current.val <= current.next.val:
                current = current.next
            else:
                prev = dummy
                while prev.next.val < current.next.val:
                    prev = prev.next
                
                temp = current.next
                current.next = temp.next
                temp.next = prev.next
                prev.next = temp
        
        return dummy.next
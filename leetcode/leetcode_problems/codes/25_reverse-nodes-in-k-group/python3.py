"""
Problem: Reverse Nodes in k-Group
Difficulty: Hard
Tags: linked_list

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
    def reverseKGroup(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
        # Check if there are k nodes remaining
        count = 0
        current = head
        while current and count < k:
            current = current.next
            count += 1
        
        if count == k:
            # Reverse k nodes
            current = self.reverseKGroup(current, k)
            while count > 0:
                next_node = head.next
                head.next = current
                current = head
                head = next_node
                count -= 1
            head = current
        
        return head
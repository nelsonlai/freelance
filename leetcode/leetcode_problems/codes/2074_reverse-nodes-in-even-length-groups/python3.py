"""
Problem: Reverse Nodes in Even Length Groups
Difficulty: Medium
Tags: linked_list

Approach: Traverse in groups, reverse even-length groups
Time Complexity: O(n) where n is number of nodes
Space Complexity: O(1)
"""

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def reverseEvenLengthGroups(self, head: Optional[ListNode]) -> Optional[ListNode]:
        if not head or not head.next:
            return head
        
        dummy = ListNode(0, head)
        prev_group_end = dummy
        group_size = 1
        
        while prev_group_end.next:
            # Count actual group size
            count = 0
            curr = prev_group_end.next
            group_end = prev_group_end
            
            while count < group_size and curr:
                group_end = curr
                curr = curr.next
                count += 1
            
            # Reverse if even length
            if count % 2 == 0:
                # Reverse the group
                prev = prev_group_end
                curr = prev_group_end.next
                
                for _ in range(count):
                    next_node = curr.next
                    curr.next = prev
                    prev = curr
                    curr = next_node
                
                # Connect reversed group
                first_in_group = prev_group_end.next
                first_in_group.next = curr
                prev_group_end.next = group_end
                prev_group_end = first_in_group
            else:
                prev_group_end = group_end
            
            group_size += 1
        
        return dummy.next
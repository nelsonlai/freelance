"""
Problem: Remove Zero Sum Consecutive Nodes from Linked List
Difficulty: Medium
Tags: hash, linked_list

Approach: Use prefix sum with hash map - if same prefix sum appears, remove nodes in between
Time Complexity: O(n) where n is number of nodes
Space Complexity: O(n) for hash map
"""

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def removeZeroSumSublists(self, head: Optional[ListNode]) -> Optional[ListNode]:
        dummy = ListNode(0)
        dummy.next = head
        prefix_sum = 0
        prefix_map = {0: dummy}
        current = head
        
        while current:
            prefix_sum += current.val
            if prefix_sum in prefix_map:
                # Remove nodes from prefix_map[prefix_sum].next to current
                prev = prefix_map[prefix_sum]
                temp = prev.next
                temp_sum = prefix_sum
                
                while temp != current:
                    temp_sum += temp.val
                    if temp_sum != prefix_sum:
                        del prefix_map[temp_sum]
                    temp = temp.next
                
                prev.next = current.next
            else:
                prefix_map[prefix_sum] = current
            current = current.next
        
        return dummy.next
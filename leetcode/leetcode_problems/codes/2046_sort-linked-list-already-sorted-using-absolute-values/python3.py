"""
Problem: Sort Linked List Already Sorted Using Absolute Values
Difficulty: Medium
Tags: array, sort, linked_list

Approach: Separate negative and positive nodes, then merge
Time Complexity: O(n) where n is number of nodes
Space Complexity: O(1)
"""

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def sortLinkedList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        if not head:
            return head
        
        # Separate negative (reverse order) and positive nodes
        neg_head = None
        pos_head = None
        neg_tail = None
        pos_tail = None
        
        curr = head
        while curr:
            next_node = curr.next
            curr.next = None
            
            if curr.val < 0:
                # Add to negative list (in reverse order)
                if neg_head is None:
                    neg_head = curr
                    neg_tail = curr
                else:
                    curr.next = neg_head
                    neg_head = curr
            else:
                # Add to positive list (in order)
                if pos_head is None:
                    pos_head = curr
                    pos_tail = curr
                else:
                    pos_tail.next = curr
                    pos_tail = curr
            
            curr = next_node
        
        # Merge negative and positive lists
        if neg_head:
            if pos_head:
                neg_tail.next = pos_head
            return neg_head
        else:
            return pos_head
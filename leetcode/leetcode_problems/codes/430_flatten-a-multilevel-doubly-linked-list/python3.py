"""
Problem: Flatten a Multilevel Doubly Linked List
Difficulty: Medium
Tags: search, linked_list

Approach: Optimized algorithm based on problem constraints
Time Complexity: O(n) to O(n^2) depending on approach
Space Complexity: O(1) to O(n) depending on approach
"""

"""
# Definition for a Node.
class Node:
    def __init__(self, val, prev, next, child):
        self.val = val
        self.prev = prev
        self.next = next
        self.child = child
"""

class Solution:
    def flatten(self, head: 'Optional[Node]') -> 'Optional[Node]':
        if not head:
            return None
        
        def flatten_helper(node):
            current = node
            tail = node
            
            while current:
                next_node = current.next
                if current.child:
                    child_head, child_tail = flatten_helper(current.child)
                    current.next = child_head
                    child_head.prev = current
                    child_tail.next = next_node
                    if next_node:
                        next_node.prev = child_tail
                    current.child = None
                    tail = child_tail
                else:
                    tail = current
                current = next_node
            
            return node, tail
        
        flatten_helper(head)
        return head
"""
Problem: Populating Next Right Pointers in Each Node II
Difficulty: Medium
Tags: tree, search, linked_list, stack

Approach: DFS or BFS traversal
Time Complexity: O(n) where n is number of nodes
Space Complexity: O(h) for recursion stack where h is height
"""

"""
# Definition for a Node.
class Node:
    def __init__(self, val: int = 0, left: 'Node' = None, right: 'Node' = None, next: 'Node' = None):
        self.val = val
        self.left = left
        self.right = right
        self.next = next
"""

class Solution:
    def connect(self, root: 'Node') -> 'Node':
        if not root:
            return root
        
        head = root
        while head:
            dummy = Node(0)
            current = dummy
            
            while head:
                if head.left:
                    current.next = head.left
                    current = current.next
                if head.right:
                    current.next = head.right
                    current = current.next
                head = head.next
            
            head = dummy.next
        
        return root
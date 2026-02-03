"""
Problem: Clone N-ary Tree
Difficulty: Medium
Tags: tree, graph, hash, search

Approach: DFS - recursively clone node and all children
Time Complexity: O(n) where n is number of nodes
Space Complexity: O(h) for recursion stack
"""

"""
# Definition for a Node.
class Node:
    def __init__(self, val: Optional[int] = None, children: Optional[List['Node']] = None):
        self.val = val
        self.children = children if children is not None else []
"""

class Solution:
    def cloneTree(self, root: 'Node') -> 'Node':
        if not root:
            return None
        
        new_node = Node(root.val)
        new_node.children = [self.cloneTree(child) for child in root.children]
        
        return new_node
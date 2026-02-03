"""
Problem: Clone Graph
Difficulty: Medium
Tags: graph, hash, search

Approach: Use hash map for O(1) lookups
Time Complexity: O(n) to O(n^2) depending on approach
Space Complexity: O(n) for hash map
"""

"""
# Definition for a Node.
class Node:
    def __init__(self, val = 0, neighbors = None):
        self.val = val
        self.neighbors = neighbors if neighbors is not None else []
"""

from typing import Optional

class Solution:
    def cloneGraph(self, node: Optional['Node']) -> Optional['Node']:
        if not node:
            return None
        
        visited = {}
        
        def clone(node):
            if node in visited:
                return visited[node]
            
            clone_node = Node(node.val)
            visited[node] = clone_node
            
            for neighbor in node.neighbors:
                clone_node.neighbors.append(clone(neighbor))
            
            return clone_node
        
        return clone(node)
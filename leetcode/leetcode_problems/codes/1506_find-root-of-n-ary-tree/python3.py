"""
Problem: Find Root of N-Ary Tree
Difficulty: Medium
Tags: array, tree, hash, search

Approach: Root appears once, all other nodes appear as children. Use XOR or sum of values
Time Complexity: O(n) where n is number of nodes
Space Complexity: O(1)
"""

"""
# Definition for a Node.
class Node:
    def __init__(self, val: Optional[int] = None, children: Optional[List['Node']] = None):
        self.val = val
        self.children = children if children is not None else []
"""

class Solution:
    def findRoot(self, tree: List['Node']) -> 'Node':
        children_set = set()
        for node in tree:
            for child in node.children:
                children_set.add(child)
        
        for node in tree:
            if node not in children_set:
                return node
        return None
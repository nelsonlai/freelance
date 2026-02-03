"""
Problem: Diameter of N-Ary Tree
Difficulty: Medium
Tags: tree, search

Approach: DFS - return max depth, diameter is max of (max1 + max2) across all nodes
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
    def diameter(self, root: 'Node') -> int:
        max_diameter = 0
        
        def dfs(node):
            nonlocal max_diameter
            if not node or not node.children:
                return 0
            
            depths = sorted([dfs(child) for child in node.children], reverse=True)
            
            if len(depths) >= 2:
                max_diameter = max(max_diameter, depths[0] + depths[1] + 2)
            elif len(depths) == 1:
                max_diameter = max(max_diameter, depths[0] + 1)
            
            return depths[0] + 1 if depths else 0
        
        dfs(root)
        return max_diameter
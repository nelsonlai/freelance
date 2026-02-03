"""
Problem: Construct Quad Tree
Difficulty: Medium
Tags: array, tree

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

"""
# Definition for a QuadTree node.
class Node:
    def __init__(self, val, isLeaf, topLeft, topRight, bottomLeft, bottomRight):
        self.val = val
        self.isLeaf = isLeaf
        self.topLeft = topLeft
        self.topRight = topRight
        self.bottomLeft = bottomLeft
        self.bottomRight = bottomRight
"""

class Solution:
    def construct(self, grid: List[List[int]]) -> 'Node':
        def build(r1, c1, r2, c2):
            if r1 == r2 and c1 == c2:
                return Node(grid[r1][c1] == 1, True, None, None, None, None)
            
            mid_r = (r1 + r2) // 2
            mid_c = (c1 + c2) // 2
            
            topLeft = build(r1, c1, mid_r, mid_c)
            topRight = build(r1, mid_c + 1, mid_r, c2)
            bottomLeft = build(mid_r + 1, c1, r2, mid_c)
            bottomRight = build(mid_r + 1, mid_c + 1, r2, c2)
            
            if (topLeft.isLeaf and topRight.isLeaf and bottomLeft.isLeaf and bottomRight.isLeaf and
                topLeft.val == topRight.val == bottomLeft.val == bottomRight.val):
                return Node(topLeft.val, True, None, None, None, None)
            
            return Node(False, False, topLeft, topRight, bottomLeft, bottomRight)
        
        n = len(grid)
        return build(0, 0, n - 1, n - 1)
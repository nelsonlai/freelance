"""
Problem: Even Odd Tree
Difficulty: Medium
Tags: tree, search, bfs

Approach: BFS - level 0 (even) should have odd values in strictly increasing order, level 1 (odd) should have even values in strictly decreasing order
Time Complexity: O(n) where n is number of nodes
Space Complexity: O(n) for queue
"""

from collections import deque

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def isEvenOddTree(self, root: Optional[TreeNode]) -> bool:
        queue = deque([root])
        level = 0
        
        while queue:
            size = len(queue)
            prev = None
            
            for _ in range(size):
                node = queue.popleft()
                
                # Check parity
                if level % 2 == 0:  # Even level - should be odd values, strictly increasing
                    if node.val % 2 == 0:
                        return False
                    if prev is not None and node.val <= prev:
                        return False
                else:  # Odd level - should be even values, strictly decreasing
                    if node.val % 2 == 1:
                        return False
                    if prev is not None and node.val >= prev:
                        return False
                
                prev = node.val
                
                if node.left:
                    queue.append(node.left)
                if node.right:
                    queue.append(node.right)
            
            level += 1
        
        return True
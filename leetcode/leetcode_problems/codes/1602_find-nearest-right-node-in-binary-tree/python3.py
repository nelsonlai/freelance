"""
Problem: Find Nearest Right Node in Binary Tree
Difficulty: Medium
Tags: tree, search, bfs

Approach: BFS - find target node, return next node at same level
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
    def findNearestRightNode(self, root: TreeNode, u: TreeNode) -> Optional[TreeNode]:
        queue = deque([root])
        
        while queue:
            size = len(queue)
            for i in range(size):
                node = queue.popleft()
                if node == u:
                    if i < size - 1:
                        return queue[0] if queue else None
                    return None
                
                if node.left:
                    queue.append(node.left)
                if node.right:
                    queue.append(node.right)
        
        return None
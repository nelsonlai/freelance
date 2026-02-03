"""
Problem: Binary Tree Vertical Order Traversal
Difficulty: Medium
Tags: tree, hash, sort, search

Approach: DFS or BFS traversal
Time Complexity: O(n) where n is number of nodes
Space Complexity: O(h) for recursion stack where h is height
"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
from collections import defaultdict, deque

class Solution:
    def verticalOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
        if not root:
            return []
        
        column_map = defaultdict(list)
        queue = deque([(root, 0)])
        
        while queue:
            node, col = queue.popleft()
            column_map[col].append(node.val)
            
            if node.left:
                queue.append((node.left, col - 1))
            if node.right:
                queue.append((node.right, col + 1))
        
        return [column_map[col] for col in sorted(column_map.keys())]
"""
Problem: Correct a Binary Tree
Difficulty: Medium
Tags: tree, hash, search, bfs

Approach: BFS - find node with invalid right child pointing to ancestor, remove it
Time Complexity: O(n) where n is number of nodes
Space Complexity: O(n) for queue and visited set
"""

from collections import deque

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def correctBinaryTree(self, root: TreeNode) -> TreeNode:
        queue = deque([(root, None, None)])  # (node, parent, is_left)
        visited = {root}
        
        while queue:
            node, parent, is_left = queue.popleft()
            
            if node.right:
                if node.right in visited:
                    if is_left:
                        parent.left = None
                    else:
                        parent.right = None
                    return root
                visited.add(node.right)
                queue.append((node.right, node, False))
            
            if node.left:
                if node.left in visited:
                    node.left = None
                    return root
                visited.add(node.left)
                queue.append((node.left, node, True))
        
        return root
"""
Problem: Number of Good Leaf Nodes Pairs
Difficulty: Medium
Tags: tree, graph, search

Approach: DFS - return list of distances to leaves, count pairs within distance
Time Complexity: O(n * distance^2) where n is number of nodes
Space Complexity: O(h) for recursion stack
"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def countPairs(self, root: Optional[TreeNode], distance: int) -> int:
        count = 0
        
        def dfs(node):
            nonlocal count
            if not node:
                return []
            
            if not node.left and not node.right:
                return [1]
            
            left_distances = dfs(node.left)
            right_distances = dfs(node.right)
            
            for left_dist in left_distances:
                for right_dist in right_distances:
                    if left_dist + right_dist <= distance:
                        count += 1
            
            return [d + 1 for d in left_distances + right_distances if d + 1 < distance]
        
        dfs(root)
        return count
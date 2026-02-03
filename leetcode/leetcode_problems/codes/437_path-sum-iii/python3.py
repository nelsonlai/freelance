"""
Problem: Path Sum III
Difficulty: Medium
Tags: tree, search

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
from collections import defaultdict

class Solution:
    def pathSum(self, root: Optional[TreeNode], targetSum: int) -> int:
        count = defaultdict(int)
        count[0] = 1
        
        def dfs(node, current_sum):
            if not node:
                return 0
            
            current_sum += node.val
            result = count[current_sum - targetSum]
            
            count[current_sum] += 1
            result += dfs(node.left, current_sum)
            result += dfs(node.right, current_sum)
            count[current_sum] -= 1
            
            return result
        
        return dfs(root, 0)
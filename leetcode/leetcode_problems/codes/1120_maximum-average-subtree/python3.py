"""
Problem: Maximum Average Subtree
Difficulty: Medium
Tags: tree, search

Approach: DFS - calculate sum and count for each subtree, track maximum average
Time Complexity: O(n) where n is number of nodes
Space Complexity: O(h) for recursion stack where h is height
"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def maximumAverageSubtree(self, root: Optional[TreeNode]) -> float:
        max_avg = 0.0
        
        def dfs(node):
            nonlocal max_avg
            if not node:
                return (0, 0)  # (sum, count)
            
            left_sum, left_count = dfs(node.left)
            right_sum, right_count = dfs(node.right)
            
            total_sum = left_sum + right_sum + node.val
            total_count = left_count + right_count + 1
            avg = total_sum / total_count
            max_avg = max(max_avg, avg)
            
            return (total_sum, total_count)
        
        dfs(root)
        return max_avg
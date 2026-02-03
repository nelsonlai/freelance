"""
Problem: Most Frequent Subtree Sum
Difficulty: Medium
Tags: tree, hash, search

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
    def findFrequentTreeSum(self, root: Optional[TreeNode]) -> List[int]:
        count = defaultdict(int)
        
        def dfs(node):
            if not node:
                return 0
            
            left_sum = dfs(node.left)
            right_sum = dfs(node.right)
            total = node.val + left_sum + right_sum
            count[total] += 1
            return total
        
        dfs(root)
        
        if not count:
            return []
        
        max_count = max(count.values())
        return [val for val, cnt in count.items() if cnt == max_count]
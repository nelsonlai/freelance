"""
Problem: Path Sum II
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
class Solution:
    def pathSum(self, root: Optional[TreeNode], targetSum: int) -> List[List[int]]:
        result = []
        
        def dfs(node, remaining, path):
            if not node:
                return
            
            path.append(node.val)
            
            if not node.left and not node.right and remaining == node.val:
                result.append(list(path))
            else:
                dfs(node.left, remaining - node.val, path)
                dfs(node.right, remaining - node.val, path)
            
            path.pop()
        
        dfs(root, targetSum, [])
        return result
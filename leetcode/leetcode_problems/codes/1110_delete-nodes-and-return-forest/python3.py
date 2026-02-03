"""
Problem: Delete Nodes And Return Forest
Difficulty: Medium
Tags: array, tree, hash, search

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def delNodes(self, root: Optional[TreeNode], to_delete: List[int]) -> List[TreeNode]:
        to_delete_set = set(to_delete)
        result = []
        
        def dfs(node, is_root):
            if not node:
                return None
            
            should_delete = node.val in to_delete_set
            
            if is_root and not should_delete:
                result.append(node)
            
            node.left = dfs(node.left, should_delete)
            node.right = dfs(node.right, should_delete)
            
            return None if should_delete else node
        
        dfs(root, True)
        return result
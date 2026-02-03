"""
Problem: Print Binary Tree
Difficulty: Medium
Tags: string, tree, search

Approach: String manipulation with hash map or two pointers
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
    def printTree(self, root: Optional[TreeNode]) -> List[List[str]]:
        def get_height(node):
            if not node:
                return 0
            return 1 + max(get_height(node.left), get_height(node.right))
        
        height = get_height(root)
        width = (1 << height) - 1
        result = [[""] * width for _ in range(height)]
        
        def fill(node, level, left, right):
            if not node:
                return
            
            mid = (left + right) // 2
            result[level][mid] = str(node.val)
            fill(node.left, level + 1, left, mid - 1)
            fill(node.right, level + 1, mid + 1, right)
        
        fill(root, 0, 0, width - 1)
        return result
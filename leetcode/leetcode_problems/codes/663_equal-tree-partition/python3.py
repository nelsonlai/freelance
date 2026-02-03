"""
Problem: Equal Tree Partition
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
    def checkEqualTree(self, root: Optional[TreeNode]) -> bool:
        seen = set()
        
        def get_sum(node):
            if not node:
                return 0
            
            total = node.val + get_sum(node.left) + get_sum(node.right)
            seen.add(total)
            return total
        
        total_sum = get_sum(root)
        seen.remove(total_sum)
        
        return total_sum % 2 == 0 and total_sum // 2 in seen
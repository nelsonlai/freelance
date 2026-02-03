"""
Problem: Insufficient Nodes in Root to Leaf Paths
Difficulty: Medium
Tags: tree, search

Approach: DFS - remove nodes if all paths through them are insufficient
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
    def sufficientSubset(self, root: Optional[TreeNode], limit: int) -> Optional[TreeNode]:
        def dfs(node, current_sum):
            if not node:
                return None, current_sum
            
            current_sum += node.val
            
            if not node.left and not node.right:
                return (node, current_sum) if current_sum >= limit else (None, current_sum)
            
            left_node, left_sum = dfs(node.left, current_sum)
            right_node, right_sum = dfs(node.right, current_sum)
            
            if not left_node and not right_node:
                return None, max(left_sum, right_sum)
            
            node.left = left_node
            node.right = right_node
            return node, max(left_sum, right_sum)
        
        result, _ = dfs(root, 0)
        return result
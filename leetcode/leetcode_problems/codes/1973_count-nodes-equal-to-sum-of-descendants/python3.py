"""
Problem: Count Nodes Equal to Sum of Descendants
Difficulty: Medium
Tags: tree, search, DFS

Approach: DFS to calculate sum of descendants, count nodes where val equals sum
Time Complexity: O(n) where n is nodes
Space Complexity: O(h) for recursion stack
"""

class Solution:
    def equalToDescendants(self, root: Optional[TreeNode]) -> int:
        count = 0
        
        def dfs(node):
            nonlocal count
            if not node:
                return 0
            
            left_sum = dfs(node.left)
            right_sum = dfs(node.right)
            descendants_sum = left_sum + right_sum
            
            if node.val == descendants_sum:
                count += 1
            
            return node.val + descendants_sum
        
        dfs(root)
        return count
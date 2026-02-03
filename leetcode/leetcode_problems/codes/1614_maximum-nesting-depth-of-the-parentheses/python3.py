"""
Problem: Maximum Nesting Depth of the Parentheses
Difficulty: Easy
Tags: string, stack

Approach: Track depth while traversing, update max depth
Time Complexity: O(n) where n is length of s
Space Complexity: O(1)
"""

class Solution:
    def maxDepth(self, s: str) -> int:
        depth = 0
        max_depth = 0
        
        for char in s:
            if char == '(':
                depth += 1
                max_depth = max(max_depth, depth)
            elif char == ')':
                depth -= 1
        
        return max_depth
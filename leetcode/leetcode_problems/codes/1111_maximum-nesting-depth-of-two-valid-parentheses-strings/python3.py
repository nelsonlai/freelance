"""
Problem: Maximum Nesting Depth of Two Valid Parentheses Strings
Difficulty: Medium
Tags: array, string, stack

Approach: Assign based on depth parity - split evenly between A and B
Time Complexity: O(n)
Space Complexity: O(1) excluding output
"""

class Solution:
    def maxDepthAfterSplit(self, seq: str) -> List[int]:
        result = []
        depth = 0
        
        for char in seq:
            if char == '(':
                depth += 1
                result.append(depth % 2)
            else:
                result.append(depth % 2)
                depth -= 1
        
        return result
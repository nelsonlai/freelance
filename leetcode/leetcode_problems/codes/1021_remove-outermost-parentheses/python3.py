"""
Problem: Remove Outermost Parentheses
Difficulty: Easy
Tags: string, stack

Approach: Track depth, skip outermost parentheses
Time Complexity: O(n)
Space Complexity: O(1) excluding output
"""

class Solution:
    def removeOuterParentheses(self, s: str) -> str:
        result = []
        depth = 0
        
        for char in s:
            if char == '(':
                if depth > 0:
                    result.append(char)
                depth += 1
            else:
                depth -= 1
                if depth > 0:
                    result.append(char)
        
        return ''.join(result)
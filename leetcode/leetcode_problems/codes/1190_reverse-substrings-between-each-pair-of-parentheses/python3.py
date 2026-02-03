"""
Problem: Reverse Substrings Between Each Pair of Parentheses
Difficulty: Medium
Tags: string, tree, stack

Approach: Use stack to track nested parentheses, reverse substrings when closing parenthesis found
Time Complexity: O(n^2) in worst case where n is length of s
Space Complexity: O(n) for stack
"""

class Solution:
    def reverseParentheses(self, s: str) -> str:
        stack = []
        current = []
        
        for char in s:
            if char == '(':
                stack.append(current)
                current = []
            elif char == ')':
                current.reverse()
                if stack:
                    current = stack.pop() + current
            else:
                current.append(char)
        
        return ''.join(current)
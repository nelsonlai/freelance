"""
Problem: Check If Word Is Valid After Substitutions
Difficulty: Medium
Tags: string, stack

Approach: Use stack - remove "abc" patterns, check if string becomes empty
Time Complexity: O(n)
Space Complexity: O(n) for stack
"""

class Solution:
    def isValid(self, s: str) -> bool:
        stack = []
        for char in s:
            stack.append(char)
            if len(stack) >= 3 and stack[-3:] == ['a', 'b', 'c']:
                stack.pop()
                stack.pop()
                stack.pop()
        return len(stack) == 0
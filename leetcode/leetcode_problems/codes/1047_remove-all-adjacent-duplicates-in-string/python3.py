"""
Problem: Remove All Adjacent Duplicates In String
Difficulty: Easy
Tags: string, stack

Approach: Use stack to remove adjacent duplicates
Time Complexity: O(n)
Space Complexity: O(n) for stack
"""

class Solution:
    def removeDuplicates(self, s: str) -> str:
        stack = []
        for char in s:
            if stack and stack[-1] == char:
                stack.pop()
            else:
                stack.append(char)
        return ''.join(stack)
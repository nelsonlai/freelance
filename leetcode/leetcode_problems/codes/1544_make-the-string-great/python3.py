"""
Problem: Make The String Great
Difficulty: Easy
Tags: string, stack

Approach: Use stack - remove adjacent characters that are same letter but different case
Time Complexity: O(n) where n is length of s
Space Complexity: O(n) for stack
"""

class Solution:
    def makeGood(self, s: str) -> str:
        stack = []
        for char in s:
            if stack and stack[-1] != char and stack[-1].lower() == char.lower():
                stack.pop()
            else:
                stack.append(char)
        return ''.join(stack)
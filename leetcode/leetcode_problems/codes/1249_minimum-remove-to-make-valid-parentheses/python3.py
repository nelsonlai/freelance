"""
Problem: Minimum Remove to Make Valid Parentheses
Difficulty: Medium
Tags: string, stack

Approach: Two passes - mark invalid parentheses, then build result without them
Time Complexity: O(n) where n is length of s
Space Complexity: O(n) for result
"""

class Solution:
    def minRemoveToMakeValid(self, s: str) -> str:
        stack = []
        to_remove = set()
        
        for i, char in enumerate(s):
            if char == '(':
                stack.append(i)
            elif char == ')':
                if stack:
                    stack.pop()
                else:
                    to_remove.add(i)
        
        to_remove.update(stack)
        
        return ''.join(char for i, char in enumerate(s) if i not in to_remove)
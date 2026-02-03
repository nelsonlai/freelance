"""
Problem: Maximum Score From Removing Substrings
Difficulty: Medium
Tags: string, greedy, stack

Approach: Use stack to remove pairs, prioritize higher scoring pair first
Time Complexity: O(n) where n is length
Space Complexity: O(n) for stack
"""

class Solution:
    def maximumGain(self, s: str, x: int, y: int) -> int:
        result = 0
        
        # Remove higher scoring pair first
        if x > y:
            first, second = 'ab', 'ba'
            score1, score2 = x, y
        else:
            first, second = 'ba', 'ab'
            score1, score2 = y, x
        
        # Remove first pair
        stack = []
        for char in s:
            if stack and stack[-1] + char == first:
                stack.pop()
                result += score1
            else:
                stack.append(char)
        
        # Remove second pair from remaining
        new_stack = []
        for char in stack:
            if new_stack and new_stack[-1] + char == second:
                new_stack.pop()
                result += score2
            else:
                new_stack.append(char)
        
        return result
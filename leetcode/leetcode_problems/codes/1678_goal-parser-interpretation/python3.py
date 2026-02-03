"""
Problem: Goal Parser Interpretation
Difficulty: Easy
Tags: string

Approach: Replace "()" with "o" and "(al)" with "al"
Time Complexity: O(n) where n is length
Space Complexity: O(n) for result
"""

class Solution:
    def interpret(self, command: str) -> str:
        return command.replace('()', 'o').replace('(al)', 'al')
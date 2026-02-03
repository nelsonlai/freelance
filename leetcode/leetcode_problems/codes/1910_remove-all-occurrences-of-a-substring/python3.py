"""
Problem: Remove All Occurrences of a Substring
Difficulty: Medium
Tags: string, stack

Approach: Use stack to simulate removal, keep removing until no more occurrences
Time Complexity: O(n * m) where n is s length, m is part length
Space Complexity: O(n)
"""

class Solution:
    def removeOccurrences(self, s: str, part: str) -> str:
        stack = []
        part_len = len(part)
        
        for char in s:
            stack.append(char)
            if len(stack) >= part_len and ''.join(stack[-part_len:]) == part:
                for _ in range(part_len):
                    stack.pop()
        
        return ''.join(stack)
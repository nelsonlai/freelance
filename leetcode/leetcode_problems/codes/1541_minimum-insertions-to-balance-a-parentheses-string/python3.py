"""
Problem: Minimum Insertions to Balance a Parentheses String
Difficulty: Medium
Tags: string, greedy, stack

Approach: Track needed right parentheses, handle ')' pairs and '(' requirements
Time Complexity: O(n) where n is length of s
Space Complexity: O(1)
"""

class Solution:
    def minInsertions(self, s: str) -> int:
        insertions = 0
        right_needed = 0
        
        for char in s:
            if char == '(':
                if right_needed % 2 == 1:
                    insertions += 1
                    right_needed -= 1
                right_needed += 2
            else:
                right_needed -= 1
                if right_needed < 0:
                    insertions += 1
                    right_needed += 2
        
        return insertions + right_needed
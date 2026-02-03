"""
Problem: Split a String in Balanced Strings
Difficulty: Easy
Tags: string, tree, greedy

Approach: Greedy - count L and R, split when counts are equal
Time Complexity: O(n) where n is length of s
Space Complexity: O(1)
"""

class Solution:
    def balancedStringSplit(self, s: str) -> int:
        count = 0
        balance = 0
        
        for char in s:
            if char == 'L':
                balance += 1
            else:
                balance -= 1
            
            if balance == 0:
                count += 1
        
        return count
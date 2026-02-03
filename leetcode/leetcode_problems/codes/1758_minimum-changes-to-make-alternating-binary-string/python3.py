"""
Problem: Minimum Changes To Make Alternating Binary String
Difficulty: Easy
Tags: string, greedy

Approach: Try two patterns: starting with 0 and starting with 1, find minimum changes
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def minOperations(self, s: str) -> int:
        changes_0 = 0  # Pattern: 0101...
        changes_1 = 0  # Pattern: 1010...
        
        for i, char in enumerate(s):
            expected_0 = '0' if i % 2 == 0 else '1'
            expected_1 = '1' if i % 2 == 0 else '0'
            
            if char != expected_0:
                changes_0 += 1
            if char != expected_1:
                changes_1 += 1
        
        return min(changes_0, changes_1)
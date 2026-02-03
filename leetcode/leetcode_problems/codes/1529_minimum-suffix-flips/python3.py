"""
Problem: Minimum Suffix Flips
Difficulty: Medium
Tags: string, greedy

Approach: Count transitions from '0' to '1' in target string
Time Complexity: O(n) where n is length of target
Space Complexity: O(1)
"""

class Solution:
    def minFlips(self, target: str) -> int:
        flips = 0
        current = '0'
        for char in target:
            if char != current:
                flips += 1
                current = char
        return flips
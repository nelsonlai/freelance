"""
Problem: Consecutive Characters
Difficulty: Easy
Tags: string, tree

Approach: Track current consecutive length, update max
Time Complexity: O(n) where n is length of s
Space Complexity: O(1)
"""

class Solution:
    def maxPower(self, s: str) -> int:
        max_power = 1
        current_power = 1
        
        for i in range(1, len(s)):
            if s[i] == s[i-1]:
                current_power += 1
                max_power = max(max_power, current_power)
            else:
                current_power = 1
        
        return max_power
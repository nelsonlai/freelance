"""
Problem: Number of Times Binary String Is Prefix-Aligned
Difficulty: Medium
Tags: array, string

Approach: Track maximum flipped index, if max equals current position count, it's aligned
Time Complexity: O(n) where n is length of flips
Space Complexity: O(1)
"""

class Solution:
    def numTimesAllBlue(self, flips: List[int]) -> int:
        max_index = 0
        count = 0
        
        for i, flip in enumerate(flips):
            max_index = max(max_index, flip)
            if max_index == i + 1:
                count += 1
        
        return count
"""
Problem: Longer Contiguous Segments of Ones than Zeros
Difficulty: Easy
Tags: string

Approach: Find longest consecutive 1s and 0s, compare
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def checkZeroOnes(self, s: str) -> bool:
        max_ones = max_zeros = 0
        current_ones = current_zeros = 0
        
        for char in s:
            if char == '1':
                current_ones += 1
                current_zeros = 0
                max_ones = max(max_ones, current_ones)
            else:
                current_zeros += 1
                current_ones = 0
                max_zeros = max(max_zeros, current_zeros)
        
        return max_ones > max_zeros
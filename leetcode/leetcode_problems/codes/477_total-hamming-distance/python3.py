"""
Problem: Total Hamming Distance
Difficulty: Medium
Tags: array, math

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def totalHammingDistance(self, nums: List[int]) -> int:
        total = 0
        n = len(nums)
        
        for i in range(32):
            count_ones = sum((num >> i) & 1 for num in nums)
            total += count_ones * (n - count_ones)
        
        return total
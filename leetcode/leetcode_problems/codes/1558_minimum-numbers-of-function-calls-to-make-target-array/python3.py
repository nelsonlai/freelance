"""
Problem: Minimum Numbers of Function Calls to Make Target Array
Difficulty: Medium
Tags: array, greedy

Approach: Count bits - each bit needs operations, count total bits and max bit position
Time Complexity: O(n * log(max(nums)))
Space Complexity: O(1)
"""

class Solution:
    def minOperations(self, nums: List[int]) -> int:
        total_bits = 0
        max_bits = 0
        
        for num in nums:
            bits = 0
            while num > 0:
                if num & 1:
                    total_bits += 1
                num >>= 1
                bits += 1
            max_bits = max(max_bits, bits)
        
        return total_bits + max(0, max_bits - 1)
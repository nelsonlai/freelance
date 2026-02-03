"""
Problem: Sum of All Subset XOR Totals
Difficulty: Easy
Tags: array, math, bit manipulation

Approach: For each bit position, count subsets where bit is set
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def subsetXORSum(self, nums: List[int]) -> int:
        result = 0
        n = len(nums)
        
        # For each bit position
        for bit in range(32):
            count = 0
            for num in nums:
                if num & (1 << bit):
                    count += 1
            
            # If count > 0, this bit contributes to 2^(n-1) subsets
            if count > 0:
                result += (1 << bit) * (1 << (n - 1))
        
        return result
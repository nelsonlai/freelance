"""
Problem: Maximum XOR for Each Query
Difficulty: Medium
Tags: array, bit manipulation

Approach: Calculate prefix XOR, find k that maximizes XOR with prefix
Time Complexity: O(n) where n is length
Space Complexity: O(n)
"""

class Solution:
    def getMaximumXor(self, nums: List[int], maximumBit: int) -> List[int]:
        prefix_xor = 0
        result = []
        max_val = (1 << maximumBit) - 1
        
        for num in nums:
            prefix_xor ^= num
        
        for num in reversed(nums):
            # Find k that maximizes prefix_xor ^ k
            k = max_val ^ prefix_xor
            result.append(k)
            prefix_xor ^= num
        
        return result
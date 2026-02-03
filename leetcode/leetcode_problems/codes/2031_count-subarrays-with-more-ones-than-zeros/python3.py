"""
Problem: Count Subarrays With More Ones Than Zeros
Difficulty: Medium
Tags: array, hash, prefix sum, binary indexed tree

Approach: Use prefix sum and BIT/Fenwick tree to count valid subarrays
Time Complexity: O(n log n) where n is length
Space Complexity: O(n)
"""

class FenwickTree:
    def __init__(self, size):
        self.size = size
        self.tree = [0] * (size + 1)
    
    def update(self, index, delta):
        index += 1
        while index <= self.size:
            self.tree[index] += delta
            index += index & -index
    
    def query(self, index):
        index += 1
        result = 0
        while index > 0:
            result += self.tree[index]
            index -= index & -index
        return result

class Solution:
    def subarraysWithMoreOnesThanZeroes(self, nums: List[int]) -> int:
        n = len(nums)
        MOD = 10**9 + 7
        
        # Convert to prefix sum: 1 -> +1, 0 -> -1
        prefix = [0] * (n + 1)
        for i in range(n):
            prefix[i + 1] = prefix[i] + (1 if nums[i] == 1 else -1)
        
        # Normalize prefix values for BIT (shift to non-negative)
        min_prefix = min(prefix)
        shift = -min_prefix + 1
        
        # Use BIT to count valid subarrays
        max_val = max(prefix) + shift
        bit = FenwickTree(max_val + 1)
        
        result = 0
        bit.update(0 + shift, 1)  # prefix[0] = 0
        
        for i in range(1, n + 1):
            # Count how many prefix[j] < prefix[i] where j < i
            count = bit.query(prefix[i] + shift - 1)
            result = (result + count) % MOD
            bit.update(prefix[i] + shift, 1)
        
        return result
"""
Problem: Minimum XOR Sum of Two Arrays
Difficulty: Hard
Tags: array, dp, bitmask

Approach: DP with bitmask - dp[mask] = min XOR sum using elements in mask
Time Complexity: O(n * 2^n) where n is length
Space Complexity: O(2^n)
"""

class Solution:
    def minimumXORSum(self, nums1: List[int], nums2: List[int]) -> int:
        n = len(nums1)
        dp = [float('inf')] * (1 << n)
        dp[0] = 0
        
        for mask in range(1 << n):
            count = bin(mask).count('1')
            if count >= n:
                continue
            
            for j in range(n):
                if not (mask & (1 << j)):
                    new_mask = mask | (1 << j)
                    dp[new_mask] = min(dp[new_mask], dp[mask] + (nums1[count] ^ nums2[j]))
        
        return dp[(1 << n) - 1]
"""
Problem: The Number of Good Subsets
Difficulty: Hard
Tags: array, dp, math, hash, bitmask

Approach: DP with bitmask - track products that are square-free
Time Complexity: O(n * 2^10) where n is length, 10 is primes <= 30
Space Complexity: O(2^10)
"""

from collections import Counter

class Solution:
    def numberOfGoodSubsets(self, nums: List[int]) -> int:
        MOD = 10**9 + 7
        primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29]
        count = Counter(nums)
        
        def get_mask(num):
            mask = 0
            for i, p in enumerate(primes):
                if num % p == 0:
                    if (num // p) % p == 0:
                        return -1
                    mask |= (1 << i)
            return mask
        
        dp = [0] * (1 << 10)
        dp[0] = 1
        
        for num in range(2, 31):
            if num not in count:
                continue
            mask = get_mask(num)
            if mask == -1:
                continue
            
            for prev_mask in range((1 << 10) - 1, -1, -1):
                if (prev_mask & mask) == 0:
                    dp[prev_mask | mask] = (dp[prev_mask | mask] + dp[prev_mask] * count[num]) % MOD
        
        result = sum(dp[1:]) % MOD
        if 1 in count:
            result = (result * pow(2, count[1], MOD)) % MOD
        
        return result
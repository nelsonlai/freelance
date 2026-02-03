"""
Problem: Count Good Meals
Difficulty: Medium
Tags: array, hash

Approach: For each number, check if sum with any previous number is power of 2
Time Complexity: O(n * 22) where 22 is max power of 2 to check
Space Complexity: O(n) for hash map
"""

from collections import Counter

class Solution:
    def countPairs(self, deliciousness: List[int]) -> int:
        MOD = 10**9 + 7
        freq = Counter()
        result = 0
        
        for num in deliciousness:
            # Check all powers of 2 up to 2^21 (max sum is 2^21)
            for power in range(22):
                target = (1 << power) - num
                if target in freq:
                    result = (result + freq[target]) % MOD
            freq[num] += 1
        
        return result
"""
Problem: Distribute Repeating Integers
Difficulty: Hard
Tags: array, dp, backtracking, bitmask

Approach: Count frequencies, use backtracking with memoization to assign quantities
Time Complexity: O(2^m * n) where m is quantity length, n is unique numbers
Space Complexity: O(2^m * n) for memoization
"""

from collections import Counter

class Solution:
    def canDistribute(self, nums: List[int], quantity: List[int]) -> bool:
        freq = Counter(nums)
        counts = sorted(freq.values(), reverse=True)
        quantity.sort(reverse=True)
        
        def backtrack(idx, counts):
            if idx == len(quantity):
                return True
            
            for i in range(len(counts)):
                if counts[i] >= quantity[idx]:
                    counts[i] -= quantity[idx]
                    if backtrack(idx + 1, counts):
                        return True
                    counts[i] += quantity[idx]
            return False
        
        return backtrack(0, list(counts))
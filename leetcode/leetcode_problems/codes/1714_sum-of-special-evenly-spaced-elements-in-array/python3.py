"""
Problem: Sum Of Special Evenly-Spaced Elements In Array
Difficulty: Hard
Tags: array, dp, math

Approach: For each query, sum elements at positions i, i+step, i+2*step, ...
Time Complexity: O(n * sqrt(n)) for preprocessing
Space Complexity: O(n * sqrt(n))
"""

class Solution:
    def solve(self, nums: List[int], queries: List[List[int]]) -> List[int]:
        MOD = 10**9 + 7
        n = len(nums)
        result = []
        
        for x, y in queries:
            total = 0
            i = x
            while i < n:
                total = (total + nums[i]) % MOD
                i += y
            result.append(total)
        
        return result
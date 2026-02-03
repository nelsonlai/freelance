"""
Problem: Number of Different Subsequences GCDs
Difficulty: Hard
Tags: array, math

Approach: For each possible GCD, check if it can be formed by a subsequence
Time Complexity: O(max * log(max)) where max is max value
Space Complexity: O(max)
"""

import math

class Solution:
    def countDifferentSubsequenceGCDs(self, nums: List[int]) -> int:
        max_num = max(nums)
        present = [False] * (max_num + 1)
        for num in nums:
            present[num] = True
        
        result = 0
        for g in range(1, max_num + 1):
            gcd_val = 0
            for multiple in range(g, max_num + 1, g):
                if present[multiple]:
                    gcd_val = math.gcd(gcd_val, multiple)
                    if gcd_val == g:
                        result += 1
                        break
        
        return result
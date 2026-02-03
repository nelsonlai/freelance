"""
Problem: Sum of Floored Pairs
Difficulty: Hard
Tags: array, math, search, prefix sum

Approach: Count frequency, use prefix sum to count pairs efficiently
Time Complexity: O(n + max * log(max)) where max is max value
Space Complexity: O(max)
"""

from collections import Counter

class Solution:
    def sumOfFlooredPairs(self, nums: List[int]) -> int:
        MOD = 10**9 + 7
        max_val = max(nums)
        count = Counter(nums)
        prefix = [0] * (max_val + 1)
        
        for i in range(1, max_val + 1):
            prefix[i] = prefix[i-1] + count[i]
        
        result = 0
        for num in count:
            freq = count[num]
            # For each multiple of num
            for multiple in range(num, max_val + 1, num):
                # Count numbers in range [multiple, multiple + num - 1]
                end = min(multiple + num - 1, max_val)
                cnt = prefix[end] - prefix[multiple - 1]
                result = (result + (multiple // num) * cnt * freq) % MOD
        
        return result
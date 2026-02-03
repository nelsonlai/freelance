"""
Problem: Subarray Sums Divisible by K
Difficulty: Medium
Tags: array, hash

Approach: Prefix sum with modulo - count subarrays with same remainder
Time Complexity: O(n)
Space Complexity: O(k) for remainder counter
"""

from collections import defaultdict

class Solution:
    def subarraysDivByK(self, nums: List[int], k: int) -> int:
        count = defaultdict(int)
        count[0] = 1
        prefix_sum = 0
        result = 0
        
        for num in nums:
            prefix_sum = (prefix_sum + num) % k
            if prefix_sum < 0:
                prefix_sum += k
            result += count[prefix_sum]
            count[prefix_sum] += 1
        
        return result
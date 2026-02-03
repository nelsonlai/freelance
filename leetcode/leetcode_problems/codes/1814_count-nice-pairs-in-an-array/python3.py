"""
Problem: Count Nice Pairs in an Array
Difficulty: Medium
Tags: array, math, hash

Approach: Rearrange equation: nums[i] - rev(nums[i]) == nums[j] - rev(nums[j])
Time Complexity: O(n * log(max)) where max is max value
Space Complexity: O(n)
"""

from collections import Counter

class Solution:
    def countNicePairs(self, nums: List[int]) -> int:
        def rev(n):
            return int(str(n)[::-1])
        
        diff_count = Counter()
        for num in nums:
            diff = num - rev(num)
            diff_count[diff] += 1
        
        result = 0
        MOD = 10**9 + 7
        for count in diff_count.values():
            result = (result + count * (count - 1) // 2) % MOD
        
        return result
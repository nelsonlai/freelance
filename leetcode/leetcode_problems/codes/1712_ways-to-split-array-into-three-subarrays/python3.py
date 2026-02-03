"""
Problem: Ways to Split Array Into Three Subarrays
Difficulty: Medium
Tags: array, search, prefix sum, binary search

Approach: Use prefix sum and binary search to find valid split points
Time Complexity: O(n log n) where n is length
Space Complexity: O(n) for prefix sum
"""

import bisect

class Solution:
    def waysToSplit(self, nums: List[int]) -> int:
        MOD = 10**9 + 7
        n = len(nums)
        prefix = [0]
        for num in nums:
            prefix.append(prefix[-1] + num)
        
        result = 0
        
        for i in range(1, n):
            left_sum = prefix[i]
            
            # Binary search for minimum j where mid_sum >= left_sum
            min_j = bisect.bisect_left(prefix, 2 * left_sum, i + 1)
            
            # Binary search for maximum j where right_sum >= mid_sum
            max_j = bisect.bisect_right(prefix, (prefix[n] + left_sum) // 2, i + 1) - 1
            
            if min_j <= max_j and max_j < n:
                result = (result + max_j - min_j + 1) % MOD
        
        return result
"""
Problem: Minimum Number of Removals to Make Mountain Array
Difficulty: Hard
Tags: array, dp, greedy, binary search, LIS

Approach: Find longest bitonic subsequence (increasing then decreasing), answer = n - length
Time Complexity: O(n log n) using binary search for LIS
Space Complexity: O(n)
"""

import bisect

class Solution:
    def minimumMountainRemovals(self, nums: List[int]) -> int:
        n = len(nums)
        
        # Calculate LIS ending at each position
        lis = []
        left = [0] * n
        for i in range(n):
            pos = bisect.bisect_left(lis, nums[i])
            if pos == len(lis):
                lis.append(nums[i])
            else:
                lis[pos] = nums[i]
            left[i] = pos + 1
        
        # Calculate LDS starting at each position
        lds = []
        right = [0] * n
        for i in range(n - 1, -1, -1):
            pos = bisect.bisect_left(lds, nums[i])
            if pos == len(lds):
                lds.append(nums[i])
            else:
                lds[pos] = nums[i]
            right[i] = pos + 1
        
        # Find maximum mountain length (peak must have both left and right > 1)
        max_mountain = 0
        for i in range(1, n - 1):
            if left[i] > 1 and right[i] > 1:
                max_mountain = max(max_mountain, left[i] + right[i] - 1)
        
        return n - max_mountain
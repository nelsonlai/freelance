"""
Problem: Minimum Absolute Sum Difference
Difficulty: Medium
Tags: array, sort, search, binary search

Approach: For each position, find closest value in nums1 using binary search
Time Complexity: O(n log n) where n is length
Space Complexity: O(n)
"""

import bisect

class Solution:
    def minAbsoluteSumDiff(self, nums1: List[int], nums2: List[int]) -> int:
        sorted_nums1 = sorted(nums1)
        total_diff = sum(abs(a - b) for a, b in zip(nums1, nums2))
        max_reduction = 0
        
        for i, (a, b) in enumerate(zip(nums1, nums2)):
            pos = bisect.bisect_left(sorted_nums1, b)
            if pos < len(sorted_nums1):
                max_reduction = max(max_reduction, abs(a - b) - abs(sorted_nums1[pos] - b))
            if pos > 0:
                max_reduction = max(max_reduction, abs(a - b) - abs(sorted_nums1[pos - 1] - b))
        
        MOD = 10**9 + 7
        return (total_diff - max_reduction) % MOD
"""
Problem: Count Pairs in Two Arrays
Difficulty: Medium
Tags: array, sort, search, binary search

Approach: Rearrange inequality, sort and use binary search
Time Complexity: O(n log n) where n is length
Space Complexity: O(n)
"""

import bisect

class Solution:
    def countPairs(self, nums1: List[int], nums2: List[int]) -> int:
        # nums1[i] + nums1[j] > nums2[i] + nums2[j]
        # => (nums1[i] - nums2[i]) + (nums1[j] - nums2[j]) > 0
        diff = [nums1[i] - nums2[i] for i in range(len(nums1))]
        diff.sort()
        
        result = 0
        for i in range(len(diff)):
            # Find j where diff[j] > -diff[i]
            target = -diff[i]
            idx = bisect.bisect_right(diff, target)
            result += len(diff) - max(idx, i + 1)
        
        return result
"""
Problem: Widest Pair of Indices With Equal Range Sum
Difficulty: Medium
Tags: array, hash, prefix sum

Approach: Use prefix sum difference, find widest pair with same difference
Time Complexity: O(n) where n is length
Space Complexity: O(n)
"""

class Solution:
    def widestPairOfIndices(self, nums1: List[int], nums2: List[int]) -> int:
        diff_map = {0: -1}
        diff = 0
        max_width = 0
        
        for i in range(len(nums1)):
            diff += nums1[i] - nums2[i]
            if diff in diff_map:
                max_width = max(max_width, i - diff_map[diff])
            else:
                diff_map[diff] = i
        
        return max_width
"""
Problem: Minimize Product Sum of Two Arrays
Difficulty: Medium
Tags: array, greedy, sort

Approach: Sort one ascending, one descending, multiply corresponding elements
Time Complexity: O(n log n) for sorting
Space Complexity: O(1)
"""

class Solution:
    def minProductSum(self, nums1: List[int], nums2: List[int]) -> int:
        nums1.sort()
        nums2.sort(reverse=True)
        return sum(nums1[i] * nums2[i] for i in range(len(nums1)))
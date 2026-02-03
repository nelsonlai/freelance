"""
Problem: Maximum Distance Between a Pair of Values
Difficulty: Medium
Tags: array, search, two pointers

Approach: Two pointers - for each i, find rightmost j where nums1[i] <= nums2[j]
Time Complexity: O(n + m) where n, m are array lengths
Space Complexity: O(1)
"""

class Solution:
    def maxDistance(self, nums1: List[int], nums2: List[int]) -> int:
        result = 0
        j = 0
        
        for i in range(len(nums1)):
            # Move j forward while nums1[i] <= nums2[j]
            while j < len(nums2) and nums1[i] <= nums2[j]:
                j += 1
            
            # j-1 is the rightmost valid position
            if j > i + 1:
                result = max(result, j - 1 - i)
        
        return result
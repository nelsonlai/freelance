"""
Problem: Get the Maximum Score
Difficulty: Hard
Tags: array, dp, greedy, sort

Approach: Two pointers - track sum in each array, at common values take maximum
Time Complexity: O(n + m) where n, m are array lengths
Space Complexity: O(1)
"""

class Solution:
    def maxSum(self, nums1: List[int], nums2: List[int]) -> int:
        MOD = 10**9 + 7
        i, j = 0, 0
        sum1, sum2 = 0, 0
        result = 0
        
        while i < len(nums1) or j < len(nums2):
            if i < len(nums1) and (j >= len(nums2) or nums1[i] < nums2[j]):
                sum1 += nums1[i]
                i += 1
            elif j < len(nums2) and (i >= len(nums1) or nums2[j] < nums1[i]):
                sum2 += nums2[j]
                j += 1
            else:
                result = (result + max(sum1, sum2) + nums1[i]) % MOD
                sum1 = sum2 = 0
                i += 1
                j += 1
        
        result = (result + max(sum1, sum2)) % MOD
        return result
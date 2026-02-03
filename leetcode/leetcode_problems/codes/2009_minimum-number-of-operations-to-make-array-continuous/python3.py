"""
Problem: Minimum Number of Operations to Make Array Continuous
Difficulty: Hard
Tags: array, hash, search, sliding window

Approach: Sort and deduplicate, use sliding window to find longest valid subarray
Time Complexity: O(n log n) for sorting
Space Complexity: O(n)
"""

class Solution:
    def minOperations(self, nums: List[int]) -> int:
        n = len(nums)
        unique = sorted(set(nums))
        m = len(unique)
        
        # Find longest subarray where unique[j] - unique[i] < n
        max_keep = 0
        j = 0
        
        for i in range(m):
            while j < m and unique[j] < unique[i] + n:
                j += 1
            max_keep = max(max_keep, j - i)
        
        return n - max_keep
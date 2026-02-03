"""
Problem: Missing Element in Sorted Array
Difficulty: Medium
Tags: array, sort, search

Approach: Binary search - find position where missing count reaches k
Time Complexity: O(log n)
Space Complexity: O(1)
"""

class Solution:
    def missingElement(self, nums: List[int], k: int) -> int:
        def missing_count(idx):
            return nums[idx] - nums[0] - idx
        
        n = len(nums)
        if k > missing_count(n - 1):
            return nums[-1] + k - missing_count(n - 1)
        
        left, right = 0, n - 1
        while left < right:
            mid = (left + right) // 2
            if missing_count(mid) < k:
                left = mid + 1
            else:
                right = mid
        
        return nums[left - 1] + k - missing_count(left - 1)
"""
Problem: Shortest Subarray to be Removed to Make Array Sorted
Difficulty: Medium
Tags: array, sort, search, stack

Approach: Find longest non-decreasing prefix and suffix, try merging them
Time Complexity: O(n) where n is length of arr
Space Complexity: O(1)
"""

class Solution:
    def findLengthOfShortestSubarray(self, arr: List[int]) -> int:
        n = len(arr)
        left = 0
        while left < n - 1 and arr[left] <= arr[left + 1]:
            left += 1
        
        if left == n - 1:
            return 0
        
        right = n - 1
        while right > 0 and arr[right - 1] <= arr[right]:
            right -= 1
        
        result = min(n - left - 1, right)
        
        i, j = 0, right
        while i <= left and j < n:
            if arr[i] <= arr[j]:
                result = min(result, j - i - 1)
                i += 1
            else:
                j += 1
        
        return result
"""
Problem: Binary Searchable Numbers in an Unsorted Array
Difficulty: Medium
Tags: array, sort, search

Approach: Number is searchable if all left are smaller and all right are larger
Time Complexity: O(n) where n is length
Space Complexity: O(n)
"""

class Solution:
    def binarySearchableNumbers(self, nums: List[int]) -> int:
        n = len(nums)
        max_left = [0] * n
        min_right = [float('inf')] * n
        
        max_left[0] = nums[0]
        for i in range(1, n):
            max_left[i] = max(max_left[i-1], nums[i])
        
        min_right[n-1] = nums[n-1]
        for i in range(n-2, -1, -1):
            min_right[i] = min(min_right[i+1], nums[i])
        
        count = 0
        for i in range(n):
            if (i == 0 or nums[i] > max_left[i-1]) and \
               (i == n-1 or nums[i] < min_right[i+1]):
                count += 1
        
        return count
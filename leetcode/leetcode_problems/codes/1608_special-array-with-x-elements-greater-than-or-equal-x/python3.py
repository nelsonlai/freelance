"""
Problem: Special Array With X Elements Greater Than or Equal X
Difficulty: Easy
Tags: array, sort, search

Approach: Sort array, for each x from 0 to n, check if exactly x elements >= x
Time Complexity: O(n log n) for sorting
Space Complexity: O(1)
"""

class Solution:
    def specialArray(self, nums: List[int]) -> int:
        nums.sort(reverse=True)
        n = len(nums)
        
        for x in range(n + 1):
            count = 0
            for num in nums:
                if num >= x:
                    count += 1
                else:
                    break
            if count == x:
                return x
        
        return -1
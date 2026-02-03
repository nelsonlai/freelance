"""
Problem: Find the Smallest Divisor Given a Threshold
Difficulty: Medium
Tags: array, search

Approach: Binary search on divisor value
Time Complexity: O(n * log(max(nums)))
Space Complexity: O(1)
"""

class Solution:
    def smallestDivisor(self, nums: List[int], threshold: int) -> int:
        def sum_with_divisor(divisor):
            return sum((num + divisor - 1) // divisor for num in nums)
        
        left, right = 1, max(nums)
        result = right
        
        while left <= right:
            mid = (left + right) // 2
            total = sum_with_divisor(mid)
            if total <= threshold:
                result = mid
                right = mid - 1
            else:
                left = mid + 1
        
        return result
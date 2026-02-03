"""
Problem: Sort Transformed Array
Difficulty: Medium
Tags: array, math, sort

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def sortTransformedArray(self, nums: List[int], a: int, b: int, c: int) -> List[int]:
        def transform(x):
            return a * x * x + b * x + c
        
        transformed = [transform(x) for x in nums]
        
        if a == 0:
            return transformed if b >= 0 else transformed[::-1]
        
        vertex = -b / (2 * a)
        result = []
        left, right = 0, len(nums) - 1
        
        while left <= right:
            if abs(nums[left] - vertex) > abs(nums[right] - vertex):
                result.append(transformed[left])
                left += 1
            else:
                result.append(transformed[right])
                right -= 1
        
        return result if a < 0 else result[::-1]
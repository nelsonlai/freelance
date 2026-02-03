"""
Problem: Minimum Operations to Make a Uni-Value Grid
Difficulty: Medium
Tags: array, math, sort

Approach: Find median value, calculate operations needed to make all cells equal
Time Complexity: O(mn log(mn)) for sorting
Space Complexity: O(mn)
"""

class Solution:
    def minOperations(self, grid: List[List[int]], x: int) -> int:
        nums = []
        for row in grid:
            nums.extend(row)
        
        # Check if all can be made equal modulo x
        remainder = nums[0] % x
        for num in nums:
            if num % x != remainder:
                return -1
        
        # Normalize all numbers
        nums = [(num - remainder) // x for num in nums]
        nums.sort()
        
        median = nums[len(nums) // 2]
        result = 0
        for num in nums:
            result += abs(num - median)
        
        return result
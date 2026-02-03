"""
Problem: Number of Valid Subarrays
Difficulty: Hard
Tags: array, stack

Approach: Monotonic stack - count subarrays where first element is minimum
Time Complexity: O(n)
Space Complexity: O(n) for stack
"""

class Solution:
    def validSubarrays(self, nums: List[int]) -> int:
        stack = []
        result = 0
        
        for i, num in enumerate(nums):
            while stack and nums[stack[-1]] > num:
                stack.pop()
            stack.append(i)
            result += len(stack)
        
        return result
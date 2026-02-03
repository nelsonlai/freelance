"""
Problem: Maximum Width Ramp
Difficulty: Medium
Tags: array, stack

Approach: Use stack to track decreasing sequence, then find maximum ramp
Time Complexity: O(n)
Space Complexity: O(n) for stack
"""

class Solution:
    def maxWidthRamp(self, nums: List[int]) -> int:
        stack = []
        # Build decreasing sequence from left
        for i, num in enumerate(nums):
            if not stack or nums[stack[-1]] > num:
                stack.append(i)
        
        max_ramp = 0
        # Traverse from right to find maximum ramp
        for j in range(len(nums) - 1, -1, -1):
            while stack and nums[stack[-1]] <= nums[j]:
                max_ramp = max(max_ramp, j - stack.pop())
        
        return max_ramp
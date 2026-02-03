"""
Problem: Maximum of Minimum Values in All Subarrays
Difficulty: Medium
Tags: array, stack, monotonic stack

Approach: For each element, find range where it's minimum, update result for that length
Time Complexity: O(n) where n is length
Space Complexity: O(n)
"""

class Solution:
    def findMaximums(self, nums: List[int]) -> List[int]:
        n = len(nums)
        result = [0] * n
        left = [-1] * n
        right = [n] * n
        stack = []
        
        # Find left boundaries
        for i in range(n):
            while stack and nums[stack[-1]] >= nums[i]:
                stack.pop()
            if stack:
                left[i] = stack[-1]
            stack.append(i)
        
        stack = []
        # Find right boundaries
        for i in range(n - 1, -1, -1):
            while stack and nums[stack[-1]] >= nums[i]:
                stack.pop()
            if stack:
                right[i] = stack[-1]
            stack.append(i)
        
        # Update result
        for i in range(n):
            length = right[i] - left[i] - 1
            result[length - 1] = max(result[length - 1], nums[i])
        
        # Fill gaps
        for i in range(n - 2, -1, -1):
            result[i] = max(result[i], result[i + 1])
        
        return result
"""
Problem: Maximum Subarray Min-Product
Difficulty: Medium
Tags: array, stack, prefix sum

Approach: Use monotonic stack to find left/right boundaries, prefix sum for range sum
Time Complexity: O(n) where n is length
Space Complexity: O(n)
"""

class Solution:
    def maxSumMinProduct(self, nums: List[int]) -> int:
        n = len(nums)
        prefix = [0]
        for num in nums:
            prefix.append(prefix[-1] + num)
        
        # Find left boundary (first index where nums[i] < nums[j])
        left = [0] * n
        stack = []
        for i in range(n):
            while stack and nums[stack[-1]] >= nums[i]:
                stack.pop()
            left[i] = stack[-1] + 1 if stack else 0
            stack.append(i)
        
        # Find right boundary
        right = [n - 1] * n
        stack = []
        for i in range(n - 1, -1, -1):
            while stack and nums[stack[-1]] >= nums[i]:
                stack.pop()
            right[i] = stack[-1] - 1 if stack else n - 1
            stack.append(i)
        
        result = 0
        for i in range(n):
            total = prefix[right[i] + 1] - prefix[left[i]]
            result = max(result, nums[i] * total)
        
        return result % (10**9 + 7)
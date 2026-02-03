"""
Problem: Find the Most Competitive Subsequence
Difficulty: Medium
Tags: array, greedy, stack, monotonic stack

Approach: Use monotonic stack - keep smallest elements while maintaining k elements
Time Complexity: O(n) where n is length
Space Complexity: O(k)
"""

class Solution:
    def mostCompetitive(self, nums: List[int], k: int) -> List[int]:
        stack = []
        n = len(nums)
        
        for i, num in enumerate(nums):
            # Remove larger elements if we can still get k elements
            while stack and stack[-1] > num and len(stack) + (n - i) > k:
                stack.pop()
            
            if len(stack) < k:
                stack.append(num)
        
        return stack
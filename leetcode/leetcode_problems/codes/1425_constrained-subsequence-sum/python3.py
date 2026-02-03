"""
Problem: Constrained Subsequence Sum
Difficulty: Hard
Tags: array, dp, queue, heap

Approach: DP with deque - dp[i] = max sum ending at i, use deque to track max in window
Time Complexity: O(n) where n is length of nums
Space Complexity: O(n) for DP and deque
"""

from collections import deque

class Solution:
    def constrainedSubsetSum(self, nums: List[int], k: int) -> int:
        n = len(nums)
        dp = [0] * n
        dq = deque()
        
        for i in range(n):
            while dq and dq[0] < i - k:
                dq.popleft()
            
            dp[i] = nums[i]
            if dq:
                dp[i] = max(dp[i], dp[dq[0]] + nums[i])
            
            while dq and dp[dq[-1]] <= dp[i]:
                dq.pop()
            
            dq.append(i)
        
        return max(dp)
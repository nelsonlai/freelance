"""
Problem: Jump Game VI
Difficulty: Medium
Tags: array, dp, queue, heap, sliding window maximum

Approach: DP with sliding window maximum - use deque to track max in window of size k
Time Complexity: O(n) where n is length
Space Complexity: O(k) for deque
"""

from collections import deque

class Solution:
    def maxResult(self, nums: List[int], k: int) -> int:
        n = len(nums)
        dp = [0] * n
        dq = deque([0])
        dp[0] = nums[0]
        
        for i in range(1, n):
            # Remove indices outside window
            while dq and dq[0] < i - k:
                dq.popleft()
            
            dp[i] = dp[dq[0]] + nums[i]
            
            # Maintain decreasing order
            while dq and dp[dq[-1]] <= dp[i]:
                dq.pop()
            
            dq.append(i)
        
        return dp[n - 1]
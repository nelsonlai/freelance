"""
Problem: Jump Game VII
Difficulty: Medium
Tags: array, string, dp, sliding window

Approach: DP with sliding window to track reachable positions
Time Complexity: O(n) where n is length
Space Complexity: O(n)
"""

from collections import deque

class Solution:
    def canReach(self, s: str, minJump: int, maxJump: int) -> bool:
        n = len(s)
        if s[-1] == '1':
            return False
        
        dp = [False] * n
        dp[0] = True
        queue = deque([0])
        
        for i in range(1, n):
            # Remove positions that are too far
            while queue and queue[0] < i - maxJump:
                queue.popleft()
            
            # Check if we can reach position i
            if s[i] == '0' and queue and queue[0] <= i - minJump:
                dp[i] = True
                queue.append(i)
        
        return dp[n - 1]
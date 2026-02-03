"""
Problem: Minimum Number of Work Sessions to Finish the Tasks
Difficulty: Medium
Tags: array, dp, bitmask

Approach: DP with bitmask - find minimum sessions to complete all tasks
Time Complexity: O(n * 2^n) where n is tasks
Space Complexity: O(2^n)
"""

from functools import lru_cache

class Solution:
    def minSessions(self, tasks: List[int], sessionTime: int) -> int:
        n = len(tasks)
        
        @lru_cache(None)
        def dp(mask):
            if mask == 0:
                return 0
            
            result = float('inf')
            # Try all subsets that fit in one session
            for submask in range(mask, 0, -1):
                if (submask & mask) != submask:
                    continue
                
                total = sum(tasks[i] for i in range(n) if (submask >> i) & 1)
                if total <= sessionTime:
                    result = min(result, 1 + dp(mask ^ submask))
            
            return result
        
        return dp((1 << n) - 1)
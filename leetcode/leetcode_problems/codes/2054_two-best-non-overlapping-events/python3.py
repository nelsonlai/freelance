"""
Problem: Two Best Non-Overlapping Events
Difficulty: Medium
Tags: array, dp, sort, search, binary search

Approach: Sort by end time, use DP with binary search to find best previous event
Time Complexity: O(n log n) where n is number of events
Space Complexity: O(n)
"""

class Solution:
    def maxTwoEvents(self, events: List[List[int]]) -> int:
        # Sort by end time
        events.sort(key=lambda x: x[1])
        n = len(events)
        
        # dp[i] = maximum value using events up to index i
        dp = [0] * n
        dp[0] = events[0][2]
        
        # Track maximum value seen so far
        max_so_far = [0] * n
        max_so_far[0] = events[0][2]
        
        result = events[0][2]
        
        for i in range(1, n):
            start, end, value = events[i]
            
            # Binary search for last event that ends before current starts
            left, right = 0, i - 1
            best_prev = -1
            
            while left <= right:
                mid = (left + right) // 2
                if events[mid][1] < start:
                    best_prev = mid
                    left = mid + 1
                else:
                    right = mid - 1
            
            # Take current event alone or with best previous
            dp[i] = value
            if best_prev >= 0:
                dp[i] = max(dp[i], max_so_far[best_prev] + value)
            
            max_so_far[i] = max(max_so_far[i - 1], dp[i])
            result = max(result, dp[i])
        
        return result
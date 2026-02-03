"""
Problem: Maximum Points You Can Obtain from Cards
Difficulty: Medium
Tags: array, dp

Approach: Sliding window - find minimum subarray of length n-k, answer is total - min
Time Complexity: O(n) where n is length of cardPoints
Space Complexity: O(1)
"""

class Solution:
    def maxScore(self, cardPoints: List[int], k: int) -> int:
        n = len(cardPoints)
        window_size = n - k
        total = sum(cardPoints)
        
        window_sum = sum(cardPoints[:window_size])
        min_window = window_sum
        
        for i in range(window_size, n):
            window_sum = window_sum - cardPoints[i - window_size] + cardPoints[i]
            min_window = min(min_window, window_sum)
        
        return total - min_window
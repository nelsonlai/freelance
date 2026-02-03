"""
Problem: Best Sightseeing Pair
Difficulty: Medium
Tags: array, dp

Approach: Track best value[i] + i seen so far, maximize with current value[j] - j
Time Complexity: O(n)
Space Complexity: O(1)
"""

class Solution:
    def maxScoreSightseeingPair(self, values: List[int]) -> int:
        best = values[0] + 0
        max_score = 0
        
        for j in range(1, len(values)):
            max_score = max(max_score, best + values[j] - j)
            best = max(best, values[j] + j)
        
        return max_score
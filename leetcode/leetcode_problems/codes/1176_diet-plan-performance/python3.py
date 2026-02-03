"""
Problem: Diet Plan Performance
Difficulty: Easy
Tags: array

Approach: Sliding window to calculate sum of k consecutive days
Time Complexity: O(n) where n is the length of calories
Space Complexity: O(1)
"""

class Solution:
    def dietPlanPerformance(self, calories: List[int], k: int, lower: int, upper: int) -> int:
        points = 0
        window_sum = sum(calories[:k])
        
        if window_sum < lower:
            points -= 1
        elif window_sum > upper:
            points += 1
        
        for i in range(k, len(calories)):
            window_sum = window_sum - calories[i-k] + calories[i]
            if window_sum < lower:
                points -= 1
            elif window_sum > upper:
                points += 1
        
        return points
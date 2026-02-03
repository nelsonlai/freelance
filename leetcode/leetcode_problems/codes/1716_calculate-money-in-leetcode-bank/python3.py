"""
Problem: Calculate Money in Leetcode Bank
Difficulty: Easy
Tags: math

Approach: Calculate sum of arithmetic sequences - each week adds 1+2+...+7, then remainder
Time Complexity: O(1)
Space Complexity: O(1)
"""

class Solution:
    def totalMoney(self, n: int) -> int:
        weeks = n // 7
        days = n % 7
        
        # Sum of first 'weeks' weeks: each week starts at (week+1) and has 7 days
        week_sum = sum((i + 1) * 7 + 21 for i in range(weeks))
        
        # Remaining days in last week
        if days > 0:
            start = weeks + 1
            week_sum += sum(start + i for i in range(days))
        
        return week_sum
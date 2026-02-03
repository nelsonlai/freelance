"""
Problem: Number of Days in a Month
Difficulty: Easy
Tags: math

Approach: Check if year is leap year, return days for the month
Time Complexity: O(1)
Space Complexity: O(1)
"""

class Solution:
    def numberOfDays(self, year: int, month: int) -> int:
        days_in_month = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
        
        # Check if leap year
        is_leap = (year % 4 == 0 and year % 100 != 0) or (year % 400 == 0)
        
        if month == 2 and is_leap:
            return 29
        return days_in_month[month - 1]
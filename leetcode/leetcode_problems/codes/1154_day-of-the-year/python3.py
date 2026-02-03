"""
Problem: Day of the Year
Difficulty: Easy
Tags: string, math

Approach: Parse date, check if leap year, calculate day of year
Time Complexity: O(1)
Space Complexity: O(1)
"""

class Solution:
    def dayOfYear(self, date: str) -> int:
        year, month, day = map(int, date.split('-'))
        days_in_month = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
        
        # Check if leap year
        is_leap = (year % 4 == 0 and year % 100 != 0) or (year % 400 == 0)
        if is_leap:
            days_in_month[1] = 29
        
        day_of_year = sum(days_in_month[:month-1]) + day
        return day_of_year
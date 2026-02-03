"""
Problem: Day of the Week
Difficulty: Easy
Tags: math

Approach: Use Zeller's congruence or datetime module
Time Complexity: O(1)
Space Complexity: O(1)
"""

class Solution:
    def dayOfTheWeek(self, day: int, month: int, year: int) -> str:
        import datetime
        days = ["Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"]
        date = datetime.date(year, month, day)
        return days[date.weekday()]
"""
Problem: Angle Between Hands of a Clock
Difficulty: Medium
Tags: math

Approach: Calculate hour and minute angles, find absolute difference, take min with 360-diff
Time Complexity: O(1)
Space Complexity: O(1)
"""

class Solution:
    def angleClock(self, hour: int, minutes: int) -> float:
        hour_angle = (hour % 12) * 30 + minutes * 0.5
        minute_angle = minutes * 6
        diff = abs(hour_angle - minute_angle)
        return min(diff, 360 - diff)
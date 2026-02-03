"""
Problem: Find the Highest Altitude
Difficulty: Easy
Tags: array, prefix sum

Approach: Calculate prefix sum, track maximum altitude
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def largestAltitude(self, gain: List[int]) -> int:
        altitude = 0
        max_altitude = 0
        
        for g in gain:
            altitude += g
            max_altitude = max(max_altitude, altitude)
        
        return max_altitude
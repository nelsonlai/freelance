"""
Problem: Distance Between Bus Stops
Difficulty: Easy
Tags: array

Approach: Calculate distance in both directions, return minimum
Time Complexity: O(n) where n is the length of distance
Space Complexity: O(1)
"""

class Solution:
    def distanceBetweenBusStops(self, distance: List[int], start: int, destination: int) -> int:
        if start > destination:
            start, destination = destination, start
        
        clockwise = sum(distance[start:destination])
        counterclockwise = sum(distance[:start]) + sum(distance[destination:])
        
        return min(clockwise, counterclockwise)
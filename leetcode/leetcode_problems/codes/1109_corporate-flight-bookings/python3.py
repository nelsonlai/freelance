"""
Problem: Corporate Flight Bookings
Difficulty: Medium
Tags: array

Approach: Difference array - mark start and end of ranges
Time Complexity: O(bookings + n)
Space Complexity: O(n)
"""

class Solution:
    def corpFlightBookings(self, bookings: List[List[int]], n: int) -> List[int]:
        result = [0] * (n + 1)
        
        for first, last, seats in bookings:
            result[first - 1] += seats
            result[last] -= seats
        
        for i in range(1, n):
            result[i] += result[i - 1]
        
        return result[:n]
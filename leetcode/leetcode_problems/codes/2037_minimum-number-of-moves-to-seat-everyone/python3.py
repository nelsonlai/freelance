"""
Problem: Minimum Number of Moves to Seat Everyone
Difficulty: Easy
Tags: array, greedy, sort

Approach: Sort both arrays, match smallest student with smallest seat
Time Complexity: O(n log n) for sorting
Space Complexity: O(1)
"""

class Solution:
    def minMovesToSeat(self, seats: List[int], students: List[int]) -> int:
        seats.sort()
        students.sort()
        
        result = 0
        for i in range(len(seats)):
            result += abs(seats[i] - students[i])
        
        return result
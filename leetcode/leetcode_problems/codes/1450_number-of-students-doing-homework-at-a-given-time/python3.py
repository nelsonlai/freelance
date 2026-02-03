"""
Problem: Number of Students Doing Homework at a Given Time
Difficulty: Easy
Tags: array

Approach: Count students where startTime <= queryTime <= endTime
Time Complexity: O(n) where n is length of arrays
Space Complexity: O(1)
"""

class Solution:
    def busyStudent(self, startTime: List[int], endTime: List[int], queryTime: int) -> int:
        return sum(1 for i in range(len(startTime)) 
                  if startTime[i] <= queryTime <= endTime[i])
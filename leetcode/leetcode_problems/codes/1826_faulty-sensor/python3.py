"""
Problem: Faulty Sensor
Difficulty: Easy
Tags: array, two pointers

Approach: Find first difference, check which sensor can be fixed by removing one element
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def badSensor(self, sensor1: List[int], sensor2: List[int]) -> int:
        n = len(sensor1)
        i = 0
        
        while i < n and sensor1[i] == sensor2[i]:
            i += 1
        
        if i == n:
            return -1
        
        # Check if sensor1 can be fixed
        can_fix_1 = True
        for j in range(i, n - 1):
            if sensor1[j] != sensor2[j + 1]:
                can_fix_1 = False
                break
        
        # Check if sensor2 can be fixed
        can_fix_2 = True
        for j in range(i, n - 1):
            if sensor1[j + 1] != sensor2[j]:
                can_fix_2 = False
                break
        
        if can_fix_1 and can_fix_2:
            return -1
        return 1 if can_fix_1 else 2
"""
Problem: Valid Mountain Array
Difficulty: Easy
Tags: array

Approach: Two pointers - find peak, then check if both sides are strictly increasing/decreasing
Time Complexity: O(n)
Space Complexity: O(1)
"""

class Solution:
    def validMountainArray(self, arr: List[int]) -> bool:
        n = len(arr)
        if n < 3:
            return False
        
        i = 0
        # Climb up
        while i < n - 1 and arr[i] < arr[i + 1]:
            i += 1
        
        # Peak can't be at start or end
        if i == 0 or i == n - 1:
            return False
        
        # Climb down
        while i < n - 1 and arr[i] > arr[i + 1]:
            i += 1
        
        return i == n - 1
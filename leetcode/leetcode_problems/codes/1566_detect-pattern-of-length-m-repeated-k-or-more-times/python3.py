"""
Problem: Detect Pattern of Length M Repeated K or More Times
Difficulty: Easy
Tags: array

Approach: Check each starting position, verify if pattern repeats k times
Time Complexity: O(n * m * k) where n is length of arr
Space Complexity: O(1)
"""

class Solution:
    def containsPattern(self, arr: List[int], m: int, k: int) -> int:
        n = len(arr)
        for i in range(n - m * k + 1):
            pattern = arr[i:i+m]
            valid = True
            for j in range(1, k):
                if arr[i + j*m:i + j*m + m] != pattern:
                    valid = False
                    break
            if valid:
                return True
        return False
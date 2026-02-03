"""
Problem: Fixed Point
Difficulty: Easy
Tags: array, sort, search

Approach: Binary search - find smallest index where arr[i] == i
Time Complexity: O(log n)
Space Complexity: O(1)
"""

class Solution:
    def fixedPoint(self, arr: List[int]) -> int:
        left, right = 0, len(arr) - 1
        result = -1
        
        while left <= right:
            mid = (left + right) // 2
            if arr[mid] == mid:
                result = mid
                right = mid - 1
            elif arr[mid] < mid:
                left = mid + 1
            else:
                right = mid - 1
        
        return result
"""
Problem: Maximum Element After Decreasing and Rearranging
Difficulty: Medium
Tags: array, greedy, sort

Approach: Sort, ensure each element is at most 1 more than previous
Time Complexity: O(n log n) for sorting
Space Complexity: O(1)
"""

class Solution:
    def maximumElementAfterDecrementingAndRearranging(self, arr: List[int]) -> int:
        arr.sort()
        arr[0] = 1
        
        for i in range(1, len(arr)):
            arr[i] = min(arr[i], arr[i-1] + 1)
        
        return arr[-1]
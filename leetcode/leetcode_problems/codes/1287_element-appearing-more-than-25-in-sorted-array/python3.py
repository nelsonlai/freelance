"""
Problem: Element Appearing More Than 25% In Sorted Array
Difficulty: Easy
Tags: array, sort

Approach: Check positions n/4, n/2, 3n/4 since array is sorted
Time Complexity: O(1) using binary search
Space Complexity: O(1)
"""

import bisect

class Solution:
    def findSpecialInteger(self, arr: List[int]) -> int:
        n = len(arr)
        positions = [n // 4, n // 2, 3 * n // 4]
        
        for pos in positions:
            num = arr[pos]
            left = bisect.bisect_left(arr, num)
            right = bisect.bisect_right(arr, num)
            if right - left > n // 4:
                return num
        
        return arr[0]
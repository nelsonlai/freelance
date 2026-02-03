"""
Problem: Kth Missing Positive Number
Difficulty: Easy
Tags: array, sort, search

Approach: Binary search - find position where missing count >= k
Time Complexity: O(log n) where n is length of arr
Space Complexity: O(1)
"""

class Solution:
    def findKthPositive(self, arr: List[int], k: int) -> int:
        left, right = 0, len(arr)
        
        while left < right:
            mid = (left + right) // 2
            missing = arr[mid] - mid - 1
            if missing < k:
                left = mid + 1
            else:
                right = mid
        
        return left + k
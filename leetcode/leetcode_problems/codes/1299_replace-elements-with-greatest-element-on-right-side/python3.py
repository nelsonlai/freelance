"""
Problem: Replace Elements with Greatest Element on Right Side
Difficulty: Easy
Tags: array

Approach: Traverse from right to left, track maximum seen so far
Time Complexity: O(n) where n is length of arr
Space Complexity: O(1) excluding result
"""

class Solution:
    def replaceElements(self, arr: List[int]) -> List[int]:
        n = len(arr)
        result = [0] * n
        max_right = -1
        
        for i in range(n - 1, -1, -1):
            result[i] = max_right
            max_right = max(max_right, arr[i])
        
        return result
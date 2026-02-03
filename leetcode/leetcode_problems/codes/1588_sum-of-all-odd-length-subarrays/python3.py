"""
Problem: Sum of All Odd Length Subarrays
Difficulty: Easy
Tags: array, math

Approach: For each element, count how many odd-length subarrays include it
Time Complexity: O(n) where n is length of arr
Space Complexity: O(1)
"""

class Solution:
    def sumOddLengthSubarrays(self, arr: List[int]) -> int:
        n = len(arr)
        result = 0
        
        for i in range(n):
            # Count odd-length subarrays that include arr[i]
            left = i + 1
            right = n - i
            odd_left = (left + 1) // 2
            odd_right = (right + 1) // 2
            even_left = left // 2
            even_right = right // 2
            
            result += arr[i] * (odd_left * odd_right + even_left * even_right)
        
        return result
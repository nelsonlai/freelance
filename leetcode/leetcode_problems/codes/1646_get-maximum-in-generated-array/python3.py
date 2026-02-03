"""
Problem: Get Maximum in Generated Array
Difficulty: Easy
Tags: array, simulation

Approach: Generate array according to rules, find maximum
Time Complexity: O(n)
Space Complexity: O(n)
"""

class Solution:
    def getMaximumGenerated(self, n: int) -> int:
        if n == 0:
            return 0
        if n == 1:
            return 1
        
        arr = [0] * (n + 1)
        arr[1] = 1
        
        for i in range(2, n + 1):
            if i % 2 == 0:
                arr[i] = arr[i // 2]
            else:
                arr[i] = arr[i // 2] + arr[i // 2 + 1]
        
        return max(arr)
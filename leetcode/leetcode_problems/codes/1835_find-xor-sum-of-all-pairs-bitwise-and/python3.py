"""
Problem: Find XOR Sum of All Pairs Bitwise AND
Difficulty: Hard
Tags: array, math, bit manipulation

Approach: (a1&b1) XOR (a1&b2) XOR ... = a1 & (b1 XOR b2 XOR ...)
Time Complexity: O(n + m) where n, m are array lengths
Space Complexity: O(1)
"""

class Solution:
    def getXORSum(self, arr1: List[int], arr2: List[int]) -> int:
        xor_arr2 = 0
        for num in arr2:
            xor_arr2 ^= num
        
        result = 0
        for num in arr1:
            result ^= (num & xor_arr2)
        
        return result
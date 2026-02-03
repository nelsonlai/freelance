"""
Problem: Find Kth Bit in Nth Binary String
Difficulty: Medium
Tags: string

Approach: Recursive - S(n) = S(n-1) + "1" + reverse(invert(S(n-1))), find position recursively
Time Complexity: O(n) where n is the problem number
Space Complexity: O(n) for recursion
"""

class Solution:
    def findKthBit(self, n: int, k: int) -> str:
        def get_bit(n, k):
            if n == 1:
                return '0'
            
            length = (1 << n) - 1
            mid = length // 2 + 1
            
            if k == mid:
                return '1'
            elif k < mid:
                return get_bit(n - 1, k)
            else:
                bit = get_bit(n - 1, length - k + 1)
                return '1' if bit == '0' else '0'
        
        return get_bit(n, k)
"""
Problem: Generate a String With Characters That Have Odd Counts
Difficulty: Easy
Tags: string

Approach: If n is odd, use n 'a's. If n is even, use (n-1) 'a's and 1 'b'
Time Complexity: O(n)
Space Complexity: O(n)
"""

class Solution:
    def generateTheString(self, n: int) -> str:
        if n % 2 == 1:
            return 'a' * n
        return 'a' * (n - 1) + 'b'
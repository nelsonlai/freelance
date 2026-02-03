"""
Problem: Next Greater Numerically Balanced Number
Difficulty: Medium
Tags: math, hash

Approach: Check numbers starting from n+1, verify if balanced
Time Complexity: O(n * log n) in worst case
Space Complexity: O(1)
"""

from collections import Counter

class Solution:
    def nextBeautifulNumber(self, n: int) -> int:
        num = n + 1
        
        while True:
            if self.isBalanced(num):
                return num
            num += 1
    
    def isBalanced(self, num: int) -> bool:
        count = Counter(str(num))
        for digit, freq in count.items():
            if int(digit) != freq:
                return False
        return True
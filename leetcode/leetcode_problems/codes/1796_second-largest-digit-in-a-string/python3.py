"""
Problem: Second Largest Digit in a String
Difficulty: Easy
Tags: string, hash

Approach: Extract digits, find second largest
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def secondHighest(self, s: str) -> int:
        digits = sorted(set(c for c in s if c.isdigit()), reverse=True)
        return int(digits[1]) if len(digits) >= 2 else -1
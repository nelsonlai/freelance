"""
Problem: Maximum Repeating Substring
Difficulty: Easy
Tags: string, dp

Approach: Try repeating word k times, find maximum k where it appears in sequence
Time Complexity: O(n * m) where n is sequence length, m is word length
Space Complexity: O(m) for repeated word
"""

class Solution:
    def maxRepeating(self, sequence: str, word: str) -> int:
        k = 0
        repeated = word
        
        while repeated in sequence:
            k += 1
            repeated += word
        
        return k
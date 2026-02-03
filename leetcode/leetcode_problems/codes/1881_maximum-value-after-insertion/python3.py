"""
Problem: Maximum Value after Insertion
Difficulty: Medium
Tags: string, greedy

Approach: Insert x at first position where it increases value
Time Complexity: O(n) where n is length
Space Complexity: O(n)
"""

class Solution:
    def maxValue(self, n: str, x: int) -> str:
        is_negative = n[0] == '-'
        
        if is_negative:
            # For negative, insert x at first position where x < digit
            for i in range(1, len(n)):
                if int(n[i]) > x:
                    return n[:i] + str(x) + n[i:]
            return n + str(x)
        else:
            # For positive, insert x at first position where x > digit
            for i in range(len(n)):
                if int(n[i]) < x:
                    return n[:i] + str(x) + n[i:]
            return n + str(x)
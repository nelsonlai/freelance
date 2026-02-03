"""
Problem: Sequential Digits
Difficulty: Medium
Tags: sort

Approach: Generate all sequential numbers, filter by range
Time Complexity: O(1) - fixed number of sequential digits
Space Complexity: O(1)
"""

class Solution:
    def sequentialDigits(self, low: int, high: int) -> List[int]:
        result = []
        for length in range(2, 10):
            for start in range(1, 11 - length):
                num = 0
                for i in range(length):
                    num = num * 10 + (start + i)
                if low <= num <= high:
                    result.append(num)
                elif num > high:
                    break
        return result
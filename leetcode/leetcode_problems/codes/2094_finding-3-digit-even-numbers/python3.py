"""
Problem: Finding 3-Digit Even Numbers
Difficulty: Easy
Tags: array, hash, backtracking

Approach: Generate all 3-digit even numbers using available digits
Time Complexity: O(n^3) where n is number of digits
Space Complexity: O(n)
"""

from collections import Counter

class Solution:
    def findEvenNumbers(self, digits: List[int]) -> List[int]:
        count = Counter(digits)
        result = set()
        
        def backtrack(num, remaining):
            if len(num) == 3:
                if num[-1] % 2 == 0:
                    result.add(int(''.join(map(str, num))))
                return
            
            for digit in range(10):
                if remaining[digit] > 0:
                    if len(num) == 0 and digit == 0:
                        continue  # Cannot start with 0
                    remaining[digit] -= 1
                    backtrack(num + [digit], remaining)
                    remaining[digit] += 1
        
        backtrack([], count.copy())
        return sorted(result)
"""
Problem: Largest Multiple of Three
Difficulty: Hard
Tags: array, string, dp, greedy, math, sort

Approach: Count digits by remainder mod 3, remove minimum digits to make sum divisible by 3
Time Complexity: O(n) where n is number of digits
Space Complexity: O(1)
"""

from collections import Counter

class Solution:
    def largestMultipleOfThree(self, digits: List[int]) -> str:
        count = Counter(digits)
        total = sum(digits)
        remainder = total % 3
        
        if remainder == 0:
            digits_to_remove = []
        elif remainder == 1:
            # Try removing one digit with remainder 1
            digits_to_remove = [i for i in [1, 4, 7] if count[i] > 0]
            if not digits_to_remove:
                # Remove two digits with remainder 2
                digits_to_remove = [i for i in [2, 5, 8] if count[i] > 0][:2]
        else:  # remainder == 2
            # Try removing one digit with remainder 2
            digits_to_remove = [i for i in [2, 5, 8] if count[i] > 0]
            if not digits_to_remove:
                # Remove two digits with remainder 1
                digits_to_remove = [i for i in [1, 4, 7] if count[i] > 0][:2]
        
        for d in digits_to_remove:
            count[d] -= 1
        
        result = ''.join(str(d) * count[d] for d in range(9, -1, -1))
        if not result:
            return ""
        if result[0] == '0':
            return "0"
        return result
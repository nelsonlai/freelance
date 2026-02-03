"""
Problem: Confusing Number
Difficulty: Easy
Tags: math

Approach: Rotate digits 180 degrees, check if result is different and valid
Time Complexity: O(log n)
Space Complexity: O(1)
"""

class Solution:
    def confusingNumber(self, n: int) -> bool:
        rotate_map = {0: 0, 1: 1, 6: 9, 8: 8, 9: 6}
        rotated = 0
        original = n
        
        while n > 0:
            digit = n % 10
            if digit not in rotate_map:
                return False
            rotated = rotated * 10 + rotate_map[digit]
            n //= 10
        
        return rotated != original
"""
Problem: Perfect Number
Difficulty: Easy
Tags: math

Approach: Optimized algorithm based on problem constraints
Time Complexity: O(n) to O(n^2) depending on approach
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def checkPerfectNumber(self, num: int) -> bool:
        if num <= 1:
            return False
        
        total = 1
        i = 2
        while i * i <= num:
            if num % i == 0:
                total += i
                if i * i != num:
                    total += num // i
            i += 1
        
        return total == num
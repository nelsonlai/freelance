"""
Problem: Subtract the Product and Sum of Digits of an Integer
Difficulty: Easy
Tags: math

Approach: Extract digits, calculate product and sum
Time Complexity: O(log n) where n is the number
Space Complexity: O(1)
"""

class Solution:
    def subtractProductAndSum(self, n: int) -> int:
        product = 1
        total = 0
        
        while n > 0:
            digit = n % 10
            product *= digit
            total += digit
            n //= 10
        
        return product - total
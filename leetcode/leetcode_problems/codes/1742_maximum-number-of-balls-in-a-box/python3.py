"""
Problem: Maximum Number of Balls in a Box
Difficulty: Easy
Tags: math, hash

Approach: Count digit sum for each number, find maximum count
Time Complexity: O(n * log(n)) where n is range
Space Complexity: O(n) for hash map
"""

from collections import Counter

class Solution:
    def countBalls(self, lowLimit: int, highLimit: int) -> int:
        def digit_sum(n):
            total = 0
            while n:
                total += n % 10
                n //= 10
            return total
        
        count = Counter()
        for num in range(lowLimit, highLimit + 1):
            count[digit_sum(num)] += 1
        
        return max(count.values())
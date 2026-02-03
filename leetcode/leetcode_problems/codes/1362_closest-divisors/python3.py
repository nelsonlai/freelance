"""
Problem: Closest Divisors
Difficulty: Medium
Tags: math

Approach: Find divisors of num+1 and num+2, return pair with smallest difference
Time Complexity: O(sqrt(num))
Space Complexity: O(1)
"""

class Solution:
    def closestDivisors(self, num: int) -> List[int]:
        def find_closest(n):
            for i in range(int(n**0.5), 0, -1):
                if n % i == 0:
                    return [i, n // i]
            return [1, n]
        
        d1 = find_closest(num + 1)
        d2 = find_closest(num + 2)
        
        if abs(d1[0] - d1[1]) < abs(d2[0] - d2[1]):
            return d1
        return d2
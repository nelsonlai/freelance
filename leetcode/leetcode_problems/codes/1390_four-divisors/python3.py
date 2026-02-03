"""
Problem: Four Divisors
Difficulty: Medium
Tags: array, math

Approach: For each number, find divisors, if exactly 4, sum them
Time Complexity: O(n * sqrt(max(nums)))
Space Complexity: O(1)
"""

class Solution:
    def sumFourDivisors(self, nums: List[int]) -> int:
        def get_divisors(num):
            divisors = []
            for i in range(1, int(num**0.5) + 1):
                if num % i == 0:
                    divisors.append(i)
                    if i != num // i:
                        divisors.append(num // i)
                if len(divisors) > 4:
                    return []
            return divisors if len(divisors) == 4 else []
        
        total = 0
        for num in nums:
            divisors = get_divisors(num)
            if len(divisors) == 4:
                total += sum(divisors)
        
        return total
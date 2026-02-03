"""
Problem: Find Missing Observations
Difficulty: Medium
Tags: array, math

Approach: Calculate total needed, distribute evenly with constraints (1-6 per die)
Time Complexity: O(n) where n is missing observations
Space Complexity: O(n)
"""

class Solution:
    def missingRolls(self, rolls: List[int], mean: int, n: int) -> List[int]:
        m = len(rolls)
        total = mean * (m + n)
        observed_sum = sum(rolls)
        missing_sum = total - observed_sum
        
        if missing_sum < n or missing_sum > 6 * n:
            return []
        
        # Distribute evenly
        base = missing_sum // n
        remainder = missing_sum % n
        
        result = [base] * n
        for i in range(remainder):
            result[i] += 1
        
        # Validate all are in range [1, 6]
        if any(x < 1 or x > 6 for x in result):
            return []
        
        return result
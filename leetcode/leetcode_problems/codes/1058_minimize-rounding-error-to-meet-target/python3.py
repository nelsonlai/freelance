"""
Problem: Minimize Rounding Error to Meet Target
Difficulty: Medium
Tags: array, string, greedy, math, sort

Approach: Round down all, then round up those with largest fractional parts
Time Complexity: O(n log n) for sorting
Space Complexity: O(n)
"""

class Solution:
    def minimizeError(self, prices: List[str], target: int) -> str:
        floor_sum = 0
        fractions = []
        
        for price in prices:
            f = float(price)
            floor_sum += int(f)
            fractions.append(f - int(f))
        
        if target < floor_sum or target > floor_sum + len(prices):
            return "-1"
        
        fractions.sort(reverse=True)
        rounds_needed = target - floor_sum
        error = sum(fractions[:rounds_needed]) + sum(1 - f for f in fractions[rounds_needed:])
        
        return f"{error:.3f}"
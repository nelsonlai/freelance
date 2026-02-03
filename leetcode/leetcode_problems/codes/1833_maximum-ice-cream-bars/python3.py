"""
Problem: Maximum Ice Cream Bars
Difficulty: Medium
Tags: array, greedy, sort

Approach: Greedy - buy cheapest ice creams first
Time Complexity: O(n log n) for sorting
Space Complexity: O(1)
"""

class Solution:
    def maxIceCream(self, costs: List[int], coins: int) -> int:
        costs.sort()
        count = 0
        
        for cost in costs:
            if coins >= cost:
                coins -= cost
                count += 1
            else:
                break
        
        return count
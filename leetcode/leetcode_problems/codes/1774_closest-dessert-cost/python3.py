"""
Problem: Closest Dessert Cost
Difficulty: Medium
Tags: array, dp, backtracking

Approach: For each base, try all topping combinations (0, 1, 2 of each)
Time Complexity: O(b * 3^t) where b is bases, t is toppings
Space Complexity: O(1)
"""

class Solution:
    def closestCost(self, baseCosts: List[int], toppingCosts: List[int], target: int) -> int:
        result = [float('inf')]
        
        def backtrack(topping_idx, current_cost):
            if topping_idx == len(toppingCosts):
                if abs(current_cost - target) < abs(result[0] - target) or \
                   (abs(current_cost - target) == abs(result[0] - target) and current_cost < result[0]):
                    result[0] = current_cost
                return
            
            # Try 0, 1, or 2 of this topping
            for count in range(3):
                backtrack(topping_idx + 1, current_cost + count * toppingCosts[topping_idx])
        
        for base in baseCosts:
            backtrack(0, base)
        
        return result[0]
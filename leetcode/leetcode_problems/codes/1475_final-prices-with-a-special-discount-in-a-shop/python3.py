"""
Problem: Final Prices With a Special Discount in a Shop
Difficulty: Easy
Tags: array, stack

Approach: For each price, find next smaller or equal price, apply discount
Time Complexity: O(n) where n is length of prices
Space Complexity: O(n) for result
"""

class Solution:
    def finalPrices(self, prices: List[int]) -> List[int]:
        result = prices[:]
        for i in range(len(prices)):
            for j in range(i + 1, len(prices)):
                if prices[j] <= prices[i]:
                    result[i] = prices[i] - prices[j]
                    break
        return result
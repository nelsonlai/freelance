"""
Problem: Product of the Last K Numbers
Difficulty: Medium
Tags: array, math

Approach: Maintain prefix products, reset on 0, use division for last k
Time Complexity: O(1) for add, O(1) for getProduct
Space Complexity: O(n) for prefix products
"""

class ProductOfNumbers:

    def __init__(self):
        self.prefix = [1]

    def add(self, num: int) -> None:
        if num == 0:
            self.prefix = [1]
        else:
            self.prefix.append(self.prefix[-1] * num)

    def getProduct(self, k: int) -> int:
        if k >= len(self.prefix):
            return 0
        return self.prefix[-1] // self.prefix[-k-1]
"""
Problem: Apply Discount Every n Orders
Difficulty: Medium
Tags: array, hash

Approach: Track order count, apply discount every nth order
Time Complexity: O(m) for getBill where m is products length
Space Complexity: O(n) for price map
"""

class Cashier:

    def __init__(self, n: int, discount: int, products: List[int], prices: List[int]):
        self.n = n
        self.discount = discount
        self.prices = {pid: price for pid, price in zip(products, prices)}
        self.count = 0

    def getBill(self, product: List[int], amount: List[int]) -> float:
        self.count += 1
        total = sum(self.prices[pid] * amt for pid, amt in zip(product, amount))
        
        if self.count % self.n == 0:
            total *= (100 - self.discount) / 100
        
        return total
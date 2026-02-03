"""
Problem: Number of Orders in the Backlog
Difficulty: Medium
Tags: array, queue, heap

Approach: Use two heaps for buy (max) and sell (min) orders
Time Complexity: O(n log n) where n is orders
Space Complexity: O(n)
"""

import heapq

class Solution:
    def getNumberOfBacklogOrders(self, orders: List[List[int]]) -> int:
        buy_orders = []  # Max heap (negate prices)
        sell_orders = []  # Min heap
        
        for price, amount, orderType in orders:
            if orderType == 0:  # Buy order
                while sell_orders and sell_orders[0][0] <= price and amount > 0:
                    sell_price, sell_amount = heapq.heappop(sell_orders)
                    if sell_amount <= amount:
                        amount -= sell_amount
                    else:
                        heapq.heappush(sell_orders, (sell_price, sell_amount - amount))
                        amount = 0
                
                if amount > 0:
                    heapq.heappush(buy_orders, (-price, amount))
            else:  # Sell order
                while buy_orders and -buy_orders[0][0] >= price and amount > 0:
                    buy_price, buy_amount = heapq.heappop(buy_orders)
                    buy_price = -buy_price
                    if buy_amount <= amount:
                        amount -= buy_amount
                    else:
                        heapq.heappush(buy_orders, (-buy_price, buy_amount - amount))
                        amount = 0
                
                if amount > 0:
                    heapq.heappush(sell_orders, (price, amount))
        
        total = sum(amount for _, amount in buy_orders) + sum(amount for _, amount in sell_orders)
        return total % (10**9 + 7)
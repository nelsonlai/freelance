"""
Problem: Shopping Offers
Difficulty: Medium
Tags: array, dp

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

from functools import lru_cache

class Solution:
    def shoppingOffers(self, price: List[int], special: List[List[int]], needs: List[int]) -> int:
        @lru_cache(None)
        def dfs(needs_tuple):
            needs_list = list(needs_tuple)
            cost = sum(price[i] * needs_list[i] for i in range(len(needs_list)))
            
            for offer in special:
                new_needs = []
                valid = True
                for i in range(len(needs_list)):
                    if needs_list[i] < offer[i]:
                        valid = False
                        break
                    new_needs.append(needs_list[i] - offer[i])
                
                if valid:
                    cost = min(cost, offer[-1] + dfs(tuple(new_needs)))
            
            return cost
        
        return dfs(tuple(needs))
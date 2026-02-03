"""
Problem: Minimized Maximum of Products Distributed to Any Store
Difficulty: Medium
Tags: array, binary search, greedy

Approach: Binary search on the maximum products per store
Time Complexity: O(m * log(max_quantity)) where m is number of products
Space Complexity: O(1)
"""

class Solution:
    def minimizedMaximum(self, n: int, quantities: List[int]) -> int:
        def canDistribute(max_per_store):
            stores_needed = 0
            for qty in quantities:
                stores_needed += (qty + max_per_store - 1) // max_per_store
            return stores_needed <= n
        
        left, right = 1, max(quantities)
        result = right
        
        while left <= right:
            mid = (left + right) // 2
            if canDistribute(mid):
                result = mid
                right = mid - 1
            else:
                left = mid + 1
        
        return result
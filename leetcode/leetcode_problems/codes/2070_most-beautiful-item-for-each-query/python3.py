"""
Problem: Most Beautiful Item for Each Query
Difficulty: Medium
Tags: array, sort, binary search

Approach: Sort items by price, use prefix max for beauty, binary search for queries
Time Complexity: O(n log n + q log n) where n is items, q is queries
Space Complexity: O(n)
"""

class Solution:
    def maximumBeauty(self, items: List[List[int]], queries: List[int]) -> List[int]:
        # Sort by price
        items.sort(key=lambda x: x[0])
        
        # Build prefix max beauty array
        prefix_max = [0] * len(items)
        prefix_max[0] = items[0][1]
        for i in range(1, len(items)):
            prefix_max[i] = max(prefix_max[i - 1], items[0][1] if i == 0 else items[i][1])
        
        result = []
        for query in queries:
            # Binary search for rightmost item with price <= query
            left, right = 0, len(items) - 1
            best_idx = -1
            
            while left <= right:
                mid = (left + right) // 2
                if items[mid][0] <= query:
                    best_idx = mid
                    left = mid + 1
                else:
                    right = mid - 1
            
            if best_idx >= 0:
                result.append(prefix_max[best_idx])
            else:
                result.append(0)
        
        return result
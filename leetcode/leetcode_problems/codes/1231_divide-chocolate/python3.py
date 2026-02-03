"""
Problem: Divide Chocolate
Difficulty: Hard
Tags: array, search

Approach: Binary search on minimum sweetness, check if can split into k+1 pieces
Time Complexity: O(n * log(sum)) where sum is total sweetness
Space Complexity: O(1)
"""

class Solution:
    def maximizeSweetness(self, sweetness: List[int], k: int) -> int:
        def can_split(min_sweet):
            pieces = 0
            current = 0
            for s in sweetness:
                current += s
                if current >= min_sweet:
                    pieces += 1
                    current = 0
            return pieces >= k + 1
        
        left, right = min(sweetness), sum(sweetness) // (k + 1)
        result = 0
        
        while left <= right:
            mid = (left + right) // 2
            if can_split(mid):
                result = mid
                left = mid + 1
            else:
                right = mid - 1
        
        return result
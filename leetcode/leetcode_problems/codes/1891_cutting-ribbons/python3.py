"""
Problem: Cutting Ribbons
Difficulty: Medium
Tags: array, search, binary search

Approach: Binary search on length, check if can get k pieces
Time Complexity: O(n log(max_length)) where max_length is max ribbon
Space Complexity: O(1)
"""

class Solution:
    def maxLength(self, ribbons: List[int], k: int) -> int:
        def canCut(length):
            count = 0
            for ribbon in ribbons:
                count += ribbon // length
            return count >= k
        
        left, right = 1, max(ribbons)
        result = 0
        
        while left <= right:
            mid = (left + right) // 2
            if canCut(mid):
                result = mid
                left = mid + 1
            else:
                right = mid - 1
        
        return result